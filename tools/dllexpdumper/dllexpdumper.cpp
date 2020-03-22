////////////////////////////////////////////////////////////////////////////
// dllexpdumper.cpp --- DLL export table dumper
// Copyright (C) 2015 Katayama Hirofumi MZ.
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#pragma comment(lib, "comdlg32.lib")    // for GetFileTitle
#pragma comment(lib, "imagehlp.lib")    // for CheckSumMappedFile

////////////////////////////////////////////////////////////////////////////

DD_Module::DD_Module() :
    m_pszFileName(NULL),
    m_hFile(INVALID_HANDLE_VALUE),
    m_hFileMapping(NULL),
    m_pFileImage(NULL),
    m_dwFileSize(0),
    m_pLoadedImage(NULL),
    m_pDOSHeader(NULL),
    m_pNTHeaders(NULL),
    m_pFileHeader(NULL),
    m_pOptional32(NULL),
    m_pOptional64(NULL),
    m_dwLastError(ERROR_SUCCESS),
    m_dwHeaderSum(0),
    m_dwCheckSum(0),
    m_pSectionHeaders(NULL),
    m_pDataDirectories(NULL)
{
}

BOOL DD_Module::LoadModule(LPCTSTR pszFileName) {
    m_hFile = ::CreateFile(pszFileName, GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, 0, NULL);
    if (m_hFile == INVALID_HANDLE_VALUE) {
        m_dwLastError = ::GetLastError();
        return FALSE;
    }

    m_dwFileSize = ::GetFileSize(m_hFile, NULL);
    if (m_dwFileSize == 0xFFFFFFFF) {
        m_dwLastError = ::GetLastError();
        ::CloseHandle(m_hFile);
        return FALSE;
    }

    m_hFileMapping = ::CreateFileMapping(
        m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (m_hFileMapping) {
        m_pFileImage = reinterpret_cast<LPBYTE>(
            ::MapViewOfFile(
                m_hFileMapping, FILE_MAP_READ, 0, 0, m_dwFileSize));
        if (m_pFileImage) {
#ifndef NO_CHECKSUM
            ::CheckSumMappedFile(m_pFileImage, m_dwFileSize,
                &m_dwHeaderSum, &m_dwCheckSum);
#endif
            if (_LoadImage(m_pFileImage)) {
                m_pszFileName = _tcsdup(pszFileName);
                return TRUE;
            }
            m_dwLastError = ERROR_INVALID_DATA;
        } else {
            m_dwLastError = ::GetLastError();
        }
        ::CloseHandle(m_hFileMapping);
        m_hFileMapping = NULL;
    } else {
        m_dwLastError = ::GetLastError();
    }

    ::CloseHandle(m_hFile);
    m_hFile = INVALID_HANDLE_VALUE;

    return FALSE;
} // DD_Module::LoadModule

void DD_Module::UnloadModule() {
    if (m_pLoadedImage) {
        ::VirtualFree(m_pLoadedImage, 0, MEM_RELEASE);
        m_pLoadedImage = NULL;
    }

    if (m_pFileImage) {
        ::UnmapViewOfFile(m_pFileImage);
        m_pFileImage = NULL;
    }

    if (m_hFileMapping) {
        ::CloseHandle(m_hFileMapping);
        m_hFileMapping = NULL;
    }

    if (m_hFile != INVALID_HANDLE_VALUE) {
        ::CloseHandle(m_hFile);
        m_hFile = INVALID_HANDLE_VALUE;
    }

    m_pszFileName = NULL;
    m_dwFileSize = 0;
    m_pDOSHeader = NULL;
    m_pNTHeaders = NULL;
    m_pFileHeader = NULL;
    m_pOptional32 = NULL;
    m_pOptional64 = NULL;
    m_dwHeaderSum = 0;
    m_dwCheckSum = 0;
    m_pSectionHeaders = NULL;
    m_pDataDirectories = NULL;
} // DD_Module::UnloadModule

BOOL DD_Module::_LoadImage(LPVOID Data) {
    PIMAGE_DOS_HEADER pDOSHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(Data);
    PIMAGE_NT_HEADERS pNTHeaders;

    // "MZ"
    if (pDOSHeader->e_magic == IMAGE_DOS_SIGNATURE && pDOSHeader->e_lfanew) {
        pNTHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
            reinterpret_cast<LPBYTE>(Data) + pDOSHeader->e_lfanew);
    } else {
        pDOSHeader = NULL;
        pNTHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(Data);
    }
    m_pDOSHeader = pDOSHeader;

    // "PE\0\0"
    if (pNTHeaders->Signature == IMAGE_NT_SIGNATURE)  {
        if (_LoadNTHeaders(pNTHeaders)) {
            m_pLoadedImage = reinterpret_cast<LPBYTE>(
                ::VirtualAlloc(NULL, GetSizeOfImage() + 16,
                               MEM_COMMIT, PAGE_READWRITE));
            assert(m_pLoadedImage);
            if (m_pLoadedImage) {
                CopyMemory(m_pLoadedImage, m_pFileImage, GetSizeOfHeaders());

                DWORD size = NumberOfSections();
                PREAL_IMAGE_SECTION_HEADER Headers = m_pSectionHeaders;
                for (DWORD i = 0; i < size; ++i) {
                    CopyMemory(
                        &m_pLoadedImage[Headers[i].RVA],
                        &m_pFileImage[Headers[i].PointerToRawData],
                        Headers[i].SizeOfRawData);
                }
                return TRUE;
            }
        }
    }

    return FALSE;
} // DD_Module::_LoadImage

BOOL DD_Module::_LoadNTHeaders(LPVOID Data) {
    m_pNTHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(Data);
    PIMAGE_FILE_HEADER pFileHeader = &m_pNTHeaders->FileHeader;

    LPBYTE pb;
    switch (pFileHeader->SizeOfOptionalHeader) {
    case sizeof(IMAGE_OPTIONAL_HEADER32):
        m_pFileHeader = pFileHeader;
        m_pOptional32 = &m_pNTHeaders32->OptionalHeader;;
        if (m_pOptional32->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
            return FALSE;

        pb = reinterpret_cast<LPBYTE>(m_pOptional32) +
             pFileHeader->SizeOfOptionalHeader;
        m_pSectionHeaders = reinterpret_cast<PREAL_IMAGE_SECTION_HEADER>(pb);
        m_pDataDirectories =
            reinterpret_cast<PREAL_IMAGE_DATA_DIRECTORY>(
                m_pOptional32->DataDirectory);
        break;

    case sizeof(IMAGE_OPTIONAL_HEADER64):
        m_pFileHeader = pFileHeader;
        m_pOptional64 = &m_pNTHeaders64->OptionalHeader;
        if (m_pOptional64->Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
            return FALSE;

        pb = reinterpret_cast<LPBYTE>(m_pOptional64) +
             pFileHeader->SizeOfOptionalHeader;
        m_pSectionHeaders = reinterpret_cast<PREAL_IMAGE_SECTION_HEADER>(pb);
        m_pDataDirectories =
            reinterpret_cast<PREAL_IMAGE_DATA_DIRECTORY>(
                m_pOptional64->DataDirectory);
        break;

    default:
        m_pFileHeader = NULL;
        m_pNTHeaders = NULL;
        m_pOptional32 = NULL;
        m_pOptional64 = NULL;
        return FALSE;
    }

    return TRUE;
} // DD_Module::_LoadNTHeaders

BOOL DD_Module::DumpExportTable(std::FILE *fp) {
    PIMAGE_EXPORT_DIRECTORY pDir = ExportDirectory();
    assert(pDir);
    if (pDir == NULL)
        return FALSE;

    // export address table (EAT)
    //LPDWORD pEAT = reinterpret_cast<LPDWORD>(GetData(pDir->AddressOfFunctions));
    // export name pointer table (ENPT)
    LPDWORD pENPT = reinterpret_cast<LPDWORD>(GetData(pDir->AddressOfNames));
    // export ordinal table (EOT)
    //LPWORD pEOT = reinterpret_cast<LPWORD>(GetData(pDir->AddressOfNameOrdinals));

    TCHAR szFileTitle[MAX_PATH];
    ::GetFileTitle(m_pszFileName, szFileTitle, MAX_PATH);
    ::CharLower(szFileTitle);

    DWORD i;
    for (i = 0; i < pDir->NumberOfNames; ++i) {
        //WORD wOrdinal = pEOT[i];
        //DWORD dwRVA = pEAT[wOrdinal];
        char *pszName = reinterpret_cast<char *>(GetData(pENPT[i]));
        //DWORD dwOrdinal = pDir->Base + wOrdinal;

        if (pszName[0] == '?' || pszName[0] == '$')
            continue;

        fprintf(fp, "%s\t", pszName);
        _fputts(szFileTitle, fp);
        fprintf(fp, "\n");
    }

    return TRUE;
} // DD_Module::DumpExportTable

////////////////////////////////////////////////////////////////////////////

extern "C"
int _tmain(int argc, _TCHAR **targv) {
    using namespace std;
    DD_Module module;
    LPTSTR pszWrite = NULL;
    LPTSTR pszAppend = NULL;
    LPTSTR pszEmpty = NULL;

    if (argc <= 1 ||
        ::lstrcmpi(targv[0], TEXT("/?")) == 0 ||
        ::lstrcmpi(targv[0], TEXT("--help")) == 0)
    {
#ifdef _WIN64
        printf("dllexpdumper64 --- 64-bit DLL export table dumper\n\n");
#else
        printf("dllexpdumper --- 32-bit DLL export table dumper\n\n");
#endif
        printf("Usage #1 (write):  dllexpdumper -w file.txt file.dll\n");
        printf("Usage #2 (append): dllexpdumper -a file.txt file.dll\n");
        printf("Usage #3 (empty):  dllexpdumper -e file.txt\n");
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        if (::lstrcmp(targv[i], TEXT("-w")) == 0) {
            if (i + 1 < argc) {
                pszWrite = targv[i + 1];
                ++i;
            } else {
                fprintf(stderr, "dllexpdumper: ERROR: argument required for '-w'\n");
                return 1;
            }
        } else if (::lstrcmp(targv[i], TEXT("-a")) == 0) {
            if (i + 1 < argc) {
                pszAppend = targv[i + 1];
                ++i;
            } else {
                fprintf(stderr, "dllexpdumper: ERROR: argument required for '-a'\n");
                return 2;
            }
        } else if (::lstrcmp(targv[i], TEXT("-e")) == 0) {
            if (i + 1 < argc) {
                pszEmpty = targv[i + 1];
                ++i;
            } else {
                fprintf(stderr, "dllexpdumper: ERROR: argument required for '-e'\n");
                return 2;
            }
        } else {
            TCHAR szFileName[MAX_PATH];
            LPTSTR pchPart;
            ::SearchPath(NULL, targv[i], NULL, MAX_PATH, szFileName, &pchPart);
            if (module.LoadModule(szFileName)) {
            } else {
                fprintf(stderr, "dllexpdumper: ERROR: Cannot load '");
                _fputts(targv[i], stderr);
                fprintf(stderr, "'\n");
            }
        }
    }

    if ((pszWrite && pszAppend) || (pszWrite && pszEmpty) ||
        (pszEmpty && pszAppend))
    {
        fprintf(stderr,
"dllexpdumper: ERROR: Select one of -w file or -a file or -e file.\n");
        return 3;
    }

    if (pszEmpty) {
        FILE *fp = _tfopen(pszEmpty, _T("w"));
        fclose(fp);
    }

    if (module.IsModuleLoaded()) {
        if (pszWrite) {
            FILE *fp = _tfopen(pszWrite, _T("w"));
            if (fp) {
                module.DumpExportTable(fp);
                fclose(fp);
            } else {
                fprintf(stderr,
                    "dllexpdumper: ERROR: Cannot open file '");
                _fputts(pszWrite, stderr);
                fprintf(stderr, "'\n");
                return 5;
            }
        } else if (pszAppend) {
            FILE *fp = _tfopen(pszAppend, _T("a"));
            if (fp) {
                module.DumpExportTable(fp);
                fclose(fp);
            } else {
                fprintf(stderr,
                    "dllexpdumper: ERROR: Cannot open file '");
                _fputts(pszAppend, stderr);
                fprintf(stderr, "'\n");
                return 6;
            }
        }
    }

    return 0;
} // _tmain

////////////////////////////////////////////////////////////////////////////
