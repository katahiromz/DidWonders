#include "stdafx.h"

void WsShowHelp(void) {
    std::cout <<
        "won32_sanitizer --- Won32 sanitizer" << std::endl <<
        "Usage: won32_sanitizer [--prefix ...] [--suffix ...]" << std::endl;
}

void WsShowVersion(void) {
    std::cout <<
#ifdef _WIN64
# ifdef __GNUC__
        "won32_sanitizer --- Won32 sanitizer for 64-bit gcc\n"
# else
        "won32_sanitizer --- Won32 sanitizer for 64-bit cl (VC++)\n"
# endif
#else
# ifdef __GNUC__
        "won32_sanitizer --- Won32 sanitizer for 32-bit gcc\n"
# else
        "won32_sanitizer --- Won32 sanitizer for 32-bit cl (VC++)\n"
# endif
#endif
        "Version 0.6" << std::endl;
}

bool WsJustDoIt(
    const std::string& prefix, const std::string& suffix)
{
    std::string suffix2 = suffix;
    if (suffix2.find(".dat") == suffix2.size() - 4) {
        suffix2.resize(suffix2.size() - 4);
    }
    std::string strOutput = prefix + "sanitize" + suffix2 + ".c";

    auto error_info = make_shared<CR_ErrorInfo>();
    #ifdef _WIN64
        CR_NameScope ns(error_info, true);
    #else
        CR_NameScope ns(error_info, false);
    #endif

    #if 0
        std::cerr << "Type [Enter] key" << std::endl;
        getchar();
    #endif

    if (!ns.LoadFromFiles(prefix, suffix)) {
        std::cerr << "ERROR: cannot load data" << std::endl;
        return false;
    }

    std::fstream out(strOutput, std::ios::out | std::ios::trunc);
    if (!out) {
        std::cerr << "ERROR: cannot create file '" <<
                     strOutput << "'" << std::endl;
        return false;
    }

    out <<
        "#include \"win32.h\"\n" << 
        "#include <stdio.h>\n" << 
        "#include <string.h>\n" << 
        "\n" << 
        "static const char fcsz[] = \"%s: size mismatched, real size is %d\\n\";\n" << 
        "static const char fcv[] = \"%s: value mismatched, real value is %lld\\n\";\n" << 
        "static const char fca[] = \"%s: alignment mismatched, real value is %d\\n\";\n" << 
        "static const char fcs[] = \"%s: value mismatched, real value is %s\\n\";\n" <<
        "static const char fcws[] = \"%ls: value mismatched, real value is %ls\\n\";\n" <<
        "static const char fcc[] = \"%ls: value mismatched\\n\";\n" <<
        "\n" << 
        "#define check_size(name,size) do { \\\n" << 
        "\tif (sizeof(name) != (size)) { \\\n" << 
        "\t\tprintf(fcsz, #name, (int)sizeof(name)); \\\n" << 
        "\t\treturn 1; \\\n" << 
        "\t} \\\n" << 
        "} while (0) \n" << 
        "\n" << 
        "#define check_value(name,value) do { \\\n" << 
        "\tif ((name) != (value)) { \\\n" << 
        "\t\tprintf(fcv, #name, (long long)name); \\\n" << 
        "\t\treturn 2; \\\n" << 
        "\t} \\\n" << 
        "} while (0) \n" << 
        "\n" <<
        "#define check_align(name,align) do { \\\n" << 
        "\tif (__alignof(name) != (align)) { \\\n" << 
        "\t\tprintf(fca, #name, (int)__alignof(name)); \\\n" << 
        "\t\treturn 3; \\\n" << 
        "\t} \\\n" << 
        "} while (0) \n" << 
        "\n" <<
        "#define check_string(name,string) do { \\\n" << 
        "\tif (lstrcmpA(name, string) != 0) { \\\n" << 
        "\t\tprintf(fcs, #name, name); \\\n" << 
        "\t\treturn 4; \\\n" << 
        "\t} \\\n" << 
        "} while (0) \n" << 
        "\n" <<
        "#define check_wstring(name,wstring) do { \\\n" << 
        "\tif (lstrcmpW(name, wstring) != 0) { \\\n" << 
        "\t\tprintf(fcws, #name, name); \\\n" << 
        "\t\treturn 5; \\\n" << 
        "\t} \\\n" << 
        "} while (0) \n" << 
        "\n" <<
        "#define check_compound(name,str,size) do { \\\n" << 
        "\tif (memcmp(&(name), (str), (size)) != 0) { \\\n" << 
        "\t\tprintf(fcc, #name); \\\n" << 
        "\t\treturn 6; \\\n" << 
        "\t} \\\n" << 
        "} while (0) \n" << 
        "\n" <<
        "int main(void) {" << std::endl;

    for (size_t i = 0; i < ns.LogTypes().size(); ++i) {
        auto type_id = i;
        auto name = ns.NameFromTypeID(type_id);
        auto& type = ns.LogType(type_id);
        auto flags = type.m_flags;
        auto size = type.m_size;
        auto align = type.m_align;

        if (name == "RASCTRYINFO" || name == "RASIPADDR" ||
            name == "LPRASCTRYINFOW" || name == "RASCTRYINFO")
        {
            continue;
        }

        if (size && name.size() && name.find("*") == std::string::npos) {
            const long excl_flags =
                (TF_ENUM | TF_FUNCTION | TF_INCOMPLETE | TF_INACCURATE);
            if (!(flags & excl_flags) && !ns.IsFuncType(type_id)) {
                out << "\tcheck_align(" << name << ", " << align << ");" <<
                       std::endl;
                out << "\tcheck_size(" << name << ", " << size << ");" <<
                       std::endl;
            }
        }
    }

    for (size_t i = 0; i < ns.LogVars().size(); ++i) {
        auto var_id = i;
        auto it = ns.MapVarIDToName().find(var_id);
        if (it == ns.MapVarIDToName().end()) {
            continue;
        }
        auto name = it->second;
        auto& var = ns.LogVar(var_id);
        auto& value = var.m_typed_value;
        if (value.m_text.empty()) {
            continue;
        }

        if (name == "MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS") {
            // This contains "defined". Not a variable. We ignore it.
            //
            // C:/Program Files (x86)/Windows Kits/8.1/include/um/winbase.h (8804)
            // #define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS (_WIN32_WINNT >= 0x0502 || !defined(_WINBASE_))
            continue;
        }

        auto type_id = value.m_type_id;
        if (ns.IsIntegralType(type_id)) {
            if (value.m_extra == "i8" || value.m_extra == "i16") {
                out << "\tcheck_value(" << name << ", " <<
                    value.m_text << ");" << std::endl;
            } else {
                out << "\tcheck_value(" << name << ", " <<
                    value.m_text << value.m_extra << ");" << std::endl;
            }
        } else if (ns.IsFloatingType(type_id)) {
            auto text = value.m_text;
            if (text == "INF" || text == "+INF") {
                out << "\tcheck_value(" << name << ", +INFINITY);" << std::endl;
            } else if (text == "-INF") {
                out << "\tcheck_value(" << name << ", -INFINITY);" << std::endl;
            } else if (text == "NAN" || text == "+NAN") {
                // NAN is incomparable
                ;
            } else if (text == "-NAN") {
                // NAN is incomparable
                ;
            } else {
                if (text.find(".") == std::string::npos &&
                    text.find("e") == std::string::npos &&
                    text.find("E") == std::string::npos)
                {
                    text += ".";
                }
                out << "\tcheck_value(" << name << ", " <<
                    text << value.m_extra << ");" << std::endl;
            }
        } else if (value.m_text[0] == '"' && ns.IsStringType(type_id)) {
            out << "\tcheck_string(" << name << ", " <<
                value.m_text << ");" << std::endl;
        } else if (value.m_text[0] == '"' && ns.IsWStringType(type_id)) {
            auto text = value.m_text;
            katahiromz::replace_string(text, "\" \"", "\" L\"");
            out << "\tcheck_wstring(" << name << ", L" <<
                text << ");" << std::endl;
        } else if (ns.IsPointerType(type_id)) {
            out << "\tcheck_value(" << name << ", (" <<
                ns.StringOfType(type_id, "") << ")" << 
                value.m_text << ");" << std::endl;
        } else if (value.m_text[0] == '{') {
            const char *ptr = reinterpret_cast<const char *>(value.m_ptr);
            std::string data(ptr, value.m_size);
            data = CrEscapeStringA2A(data);
            out << "\tcheck_compound(" << name << ", " <<
                data << ", " << ns.SizeOfType(type_id) << ");" << std::endl;
        }
    }

    out <<
        "\tputs(\"success\");\n" <<
        "\treturn 0;\n" <<
        "}" << std::endl;
    out.close();
    return true;
}

int main(int argc, char **argv) {
    bool show_help = false;
    bool show_version = false;
    const char *prefix = "";
    const char *suffix = ".dat";

#if 0
    printf("Hit [Enter] key!");
    getchar();
#endif

    for (int i = 1; i < argc; ++i) {
        if (_stricmp(argv[i], "/?") == 0 ||
            _stricmp(argv[i], "--help") == 0)
        {
            show_help = true;
        } else if (_stricmp(argv[i], "--version") == 0 ||
                   _stricmp(argv[i], "/version") == 0)
        {
            show_version = true;
        } else if (_stricmp(argv[i], "--prefix") == 0 ||
                   _stricmp(argv[i], "-p") == 0) {
            ++i;
            prefix = argv[i];
        } else if (_stricmp(argv[i], "--suffix") == 0 ||
                   _stricmp(argv[i], "-s") == 0)
        {
            ++i;
            suffix = argv[i];
        } else {
            std::cerr << "ERROR: Invalid option '" << argv[i] <<
                         "'." << std::endl;
            return 1;
        }
    }

    if (show_help) {
        WsShowHelp();
        return 0;
    }

    if (show_version) {
        WsShowVersion();
        return 0;
    }

    WsJustDoIt(prefix, suffix);

    return 0;
}
