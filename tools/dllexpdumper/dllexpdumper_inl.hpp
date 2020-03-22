////////////////////////////////////////////////////////////////////////////
// dllexpdumper_inl.hpp --- DLL export table dumper
// Copyright (C) 2015 Katayama Hirofumi MZ.
////////////////////////////////////////////////////////////////////////////

inline /*virtual*/ DD_Module::~DD_Module() {
    if (IsModuleLoaded()) {
        UnloadModule();
    }
    free(m_pszFileName);
}

inline BOOL DD_Module::IsModuleLoaded() const {
    return m_pszFileName != NULL;
}

inline BOOL DD_Module::Is32Bit() const {
    return m_pOptional32 != NULL;
}

inline BOOL DD_Module::Is64Bit() const {
    return m_pOptional64 != NULL;
}

inline DWORD DD_Module::NumberOfSections() const {
    assert(m_pFileHeader);
    return m_pFileHeader->NumberOfSections;
}

inline DWORD DD_Module::GetSizeOfHeaders() const {
    if (Is64Bit())
        return m_pOptional64->SizeOfHeaders;
    else if (Is32Bit())
        return m_pOptional32->SizeOfHeaders;
    else
        return 0;
}

inline DWORD DD_Module::GetSizeOfImage() const {
    if (Is64Bit())
        return m_pOptional64->SizeOfImage;
    else if (Is32Bit())
        return m_pOptional32->SizeOfImage;
    else
        return 0;
}

inline DWORD DD_Module::LastError() const {
    return m_dwLastError;
}

inline PIMAGE_IMPORT_DESCRIPTOR DD_Module::ImportDescriptors() {
    return reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(
        DirEntryData(IMAGE_DIRECTORY_ENTRY_IMPORT));
}

inline PIMAGE_EXPORT_DIRECTORY DD_Module::ExportDirectory() {
    return reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(
        DirEntryData(IMAGE_DIRECTORY_ENTRY_EXPORT));
}

inline PIMAGE_RESOURCE_DIRECTORY DD_Module::ResourceDirectory() {
    return reinterpret_cast<PIMAGE_RESOURCE_DIRECTORY>(
        DirEntryData(IMAGE_DIRECTORY_ENTRY_RESOURCE));
}

inline DWORD DD_Module::DirEntryDataSize(DWORD index) const {
    if (m_pDataDirectories == NULL)
        return 0;
    return (index < IMAGE_NUMBEROF_DIRECTORY_ENTRIES ?
        m_pDataDirectories[index].Size : 0);
}

inline BOOL DD_Module::IsDLL() const {
    if (!IsModuleLoaded())
        return FALSE;

    return (m_pFileHeader->Characteristics & IMAGE_FILE_DLL) != 0;
}

inline LPBYTE DD_Module::GetData(DWORD rva) {
    return (m_pLoadedImage ? m_pLoadedImage + rva : NULL);
}

inline DWORD DD_Module::RVAFromVA32(DWORD va) const {
    assert(m_pOptional32);
    return va - m_pOptional32->ImageBase;
}

inline DWORD DD_Module::RVAFromVA64(DWORDLONG va) const {
    assert(m_pOptional64);
    return (DWORD)(va - m_pOptional64->ImageBase);
}

inline DWORD DD_Module::VA32FromRVA(DWORD rva) const {
    assert(m_pOptional32);
    return m_pOptional32->ImageBase + rva;
}

inline DWORDLONG DD_Module::VA64FromRVA(DWORD rva) const {
    assert(m_pOptional64);
    return m_pOptional64->ImageBase + rva;
}

inline PREAL_IMAGE_SECTION_HEADER DD_Module::SectionHeader(DWORD index) {
    assert(m_pSectionHeaders);
    if (index < NumberOfSections())
        return &m_pSectionHeaders[index];
    return NULL;
}

inline const REAL_IMAGE_SECTION_HEADER *
DD_Module::SectionHeader(DWORD index) const {
    assert(m_pSectionHeaders);
    if (index < NumberOfSections())
        return &m_pSectionHeaders[index];
    return NULL;
}

inline PREAL_IMAGE_DATA_DIRECTORY DD_Module::DataDirectory(DWORD index) {
    assert(m_pDataDirectories);
    assert(index < IMAGE_NUMBEROF_DIRECTORY_ENTRIES);
    return &m_pDataDirectories[index];
}

inline const REAL_IMAGE_DATA_DIRECTORY *
DD_Module::DataDirectory(DWORD index) const {
    assert(m_pDataDirectories);
    assert(index < IMAGE_NUMBEROF_DIRECTORY_ENTRIES);
    return &m_pDataDirectories[index];
}

inline BOOL DD_Module::IsCheckSumValid() const {
    assert(IsModuleLoaded());
    if (Is64Bit()) {
        return m_pOptional64->CheckSum == 0 ||
               m_pOptional64->CheckSum == m_dwCheckSum;
    } else if (Is32Bit()) {
        return m_pOptional32->CheckSum == 0 ||
               m_pOptional32->CheckSum == m_dwCheckSum;
    }
    return FALSE;
}

inline LPBYTE DD_Module::DirEntryData(DWORD index) {
    if (m_pDataDirectories && index < IMAGE_NUMBEROF_DIRECTORY_ENTRIES) {
        if (m_pDataDirectories[index].RVA && m_pDataDirectories[index].Size) {
            return m_pLoadedImage + m_pDataDirectories[index].RVA;
        }
    }
    return NULL;
}

inline BOOL DD_Module::IsCUIExe() const {
    if (!IsModuleLoaded() || IsDLL())
        return FALSE;

    if (Is64Bit())
        return m_pOptional64->Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI;
    else if (Is32Bit())
        return m_pOptional32->Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI;
    else
        return FALSE;
}

inline BOOL DD_Module::IsGUIExe() const {
    if (!IsModuleLoaded() || IsDLL())
        return FALSE;

    if (Is64Bit())
        return m_pOptional64->Subsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI;
    else if (Is32Bit())
        return m_pOptional32->Subsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI;
    else
        return FALSE;
}

inline BOOL DD_Module::RVAInDirEntry(DWORD rva, DWORD index) const {
    assert(IsModuleLoaded());
    return (
        index < IMAGE_NUMBEROF_DIRECTORY_ENTRIES &&
        m_pDataDirectories[index].RVA <= rva &&
        rva < m_pDataDirectories[index].RVA +
              m_pDataDirectories[index].Size);
}

inline BOOL DD_Module::IsValidAddr32(DWORD addr) const {
    if (!Is32Bit())
        return FALSE;
    const DWORD begin = m_pOptional32->ImageBase;
    const DWORD end = begin + m_pOptional32->SizeOfImage;
    return begin <= addr && addr < end;
}

inline BOOL DD_Module::IsValidAddr64(DWORDLONG addr) const {
    if (!Is64Bit())
        return FALSE;
    const DWORDLONG begin = m_pOptional64->ImageBase;
    const DWORDLONG end = begin + m_pOptional64->SizeOfImage;
    return begin <= addr && addr < end;
}

inline DWORD DD_Module::GetBaseOfCode() const {
    if (Is64Bit())
        return m_pOptional64->BaseOfCode;
    else if (Is32Bit())
        return m_pOptional32->BaseOfCode;
    else
        return 0;
}

inline DWORD DD_Module::RVAOfEntryPoint() const {
    if (Is64Bit())
        return m_pOptional64->AddressOfEntryPoint;
    else if (Is32Bit())
        return m_pOptional32->AddressOfEntryPoint;
    else
        return 0;
}
