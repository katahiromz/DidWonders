////////////////////////////////////////////////////////////////////////////
// dllexpdumper.hpp --- DLL export table dumper
// Copyright (C) 2015 Katayama Hirofumi MZ.
////////////////////////////////////////////////////////////////////////////

#ifndef DLLEXPDUMPER_HPP_
#define DLLEXPDUMPER_HPP_

////////////////////////////////////////////////////////////////////////////
// REAL_IMAGE_SECTION_HEADER, REAL_IMAGE_DATA_DIRECTORY

#include <pshpack1.h>
typedef struct _REAL_IMAGE_SECTION_HEADER {
    BYTE        Name[IMAGE_SIZEOF_SHORT_NAME];
    union {
        DWORD   PhysicalAddress;
        DWORD   VirtualSize;
    } Misc;
    DWORD       RVA;    // Not VirtualAddress!
    DWORD       SizeOfRawData;
    DWORD       PointerToRawData;
    DWORD       PointerToRelocations;
    DWORD       PointerToLinenumbers;
    WORD        NumberOfRelocations;
    WORD        NumberOfLinenumbers;
    DWORD       Characteristics;
} REAL_IMAGE_SECTION_HEADER, *PREAL_IMAGE_SECTION_HEADER;
#include <poppack.h>

#include <pshpack1.h>
typedef struct _REAL_IMAGE_DATA_DIRECTORY {
    DWORD RVA;  // Not VirtualAddress!
    DWORD Size;
} REAL_IMAGE_DATA_DIRECTORY, *PREAL_IMAGE_DATA_DIRECTORY;
#include <poppack.h>

////////////////////////////////////////////////////////////////////////////
// Module

class DD_Module {
public:
    DD_Module();
    virtual ~DD_Module();

    BOOL LoadModule(LPCTSTR pszFileName);
    void UnloadModule();
    BOOL IsModuleLoaded() const;

    BOOL IsDLL() const;
    BOOL IsCUIExe() const;
    BOOL IsGUIExe() const;
    BOOL Is32Bit() const;
    BOOL Is64Bit() const;
    BOOL IsCheckSumValid() const;

    DWORD GetSizeOfHeaders() const;
    DWORD GetSizeOfImage() const;
    DWORD GetBaseOfCode() const;
    LPBYTE GetData(DWORD rva);
    DWORD RVAOfEntryPoint() const;

    DWORD NumberOfSections() const;
          PREAL_IMAGE_SECTION_HEADER SectionHeader(DWORD index);
    const REAL_IMAGE_SECTION_HEADER *SectionHeader(DWORD index) const;

          PREAL_IMAGE_DATA_DIRECTORY DataDirectory(DWORD index);
    const REAL_IMAGE_DATA_DIRECTORY *DataDirectory(DWORD index) const;

    DWORD LastError() const;

    LPBYTE DirEntryData(DWORD index);
    DWORD DirEntryDataSize(DWORD index) const;
    BOOL RVAInDirEntry(DWORD rva, DWORD index) const;

    BOOL IsValidAddr32(DWORD addr) const;
    BOOL IsValidAddr64(DWORDLONG addr) const;

    DWORD RVAFromVA32(DWORD va) const;
    DWORD RVAFromVA64(DWORDLONG va) const;
    DWORD VA32FromRVA(DWORD rva) const;
    DWORDLONG VA64FromRVA(DWORD rva) const;

    PIMAGE_IMPORT_DESCRIPTOR    ImportDescriptors();
    PIMAGE_EXPORT_DIRECTORY     ExportDirectory();
    PIMAGE_RESOURCE_DIRECTORY   ResourceDirectory();

    BOOL DumpExportTable(std::FILE *fp);

protected:
    LPTSTR                          m_pszFileName;
    HANDLE                          m_hFile;
    HANDLE                          m_hFileMapping;
    LPBYTE                          m_pFileImage;
    DWORD                           m_dwFileSize;
    LPBYTE                          m_pLoadedImage;
    PIMAGE_DOS_HEADER               m_pDOSHeader;
    union {
        PIMAGE_NT_HEADERS           m_pNTHeaders;
        PIMAGE_NT_HEADERS32         m_pNTHeaders32;
        PIMAGE_NT_HEADERS64         m_pNTHeaders64;
    };
    PIMAGE_FILE_HEADER              m_pFileHeader;
    PIMAGE_OPTIONAL_HEADER32        m_pOptional32;
    PIMAGE_OPTIONAL_HEADER64        m_pOptional64;
    DWORD                           m_dwLastError;
    DWORD                           m_dwHeaderSum;
    DWORD                           m_dwCheckSum;
    PREAL_IMAGE_SECTION_HEADER      m_pSectionHeaders;
    PREAL_IMAGE_DATA_DIRECTORY      m_pDataDirectories;

    BOOL _LoadImage(LPVOID Data);
    BOOL _LoadNTHeaders(LPVOID Data);
}; // class DD_Module

////////////////////////////////////////////////////////////////////////////
// inline functions

#include "dllexpdumper_inl.hpp"

////////////////////////////////////////////////////////////////////////////

#endif  // ndef DLLEXPDUMPER_HPP_
