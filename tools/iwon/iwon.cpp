#include "stdafx.h"

void IwShowLogo(void) {
    std::cerr <<
        "############################################" << std::endl <<
        "# iwon --- Won32 interactive by katahiromz #" << std::endl <<
        "# Wonders API Database (Won32)             #" << std::endl <<
        "# katayama.hirofumi.mz@gmail.com           #" << std::endl <<
        "############################################" << std::endl;
}

void IwShowHelp(void) {
    std::cout <<
        "iwon --- Won32 interactive" << std::endl <<
        "Usage: iwon [--prefix ...] [--suffix ...] [type or constant]" << std::endl;
}

void IwShowVersion(void) {
    std::cout <<
#ifdef _WIN64
# ifdef __GNUC__
        "iwon --- Won32 interactive for 64-bit gcc\n"
# else
        "iwon --- Won32 interactive for 64-bit cl (VC++)\n"
# endif
#else
# ifdef __GNUC__
        "iwon --- Won32 interactive for 32-bit gcc\n"
# else
        "iwon --- Won32 interactive for 32-bit cl (VC++)\n"
# endif
#endif
        "Version 0.7" << std::endl;
}

bool IwDoType(CR_NameScope& ns, CR_TypeID tid, const std::string& target, const std::string& name) {
    auto rtid = ns.ResolveAlias(tid);
    auto& type = ns.LogType(tid);
    auto& rtype = ns.LogType(rtid);

    if (type.m_location.m_file == "(predefined)") {
        if (target != name) {
            std::cout << name << " (" << target << ") is a predefined type." << std::endl;
        } else {
            std::cout << target << " is a predefined type." << std::endl;
        }
    } else {
        // type
        if (rtype.m_flags & TF_STRUCT) {
            // struct type
            std::cout << target << " is a struct type, defined at " <<
                         type.m_location.str() << "." << std::endl;
            if (tid != rtid) {
                std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
            } else {
                std::cout << CrTabToSpace(ns.StringOfType(tid, "", true)) << ";" << std::endl;
            }
            std::cout << "[MEMBERS]" << std::endl;
            std::cout << "NAME / OFFSET / SIZE / #TYPE_ID / BIT_OFFSET / BITS" << std::endl;
            std::cout << "-----------------------------------------------------------" << std::endl;
            auto& ls = ns.LogStruct(rtype.m_sub_id);
            for (auto& member : ls.m_members) {
                auto name = member.m_name;
                if (name.empty()) {
                    name = "(no name)";
                }
                auto tid = member.m_type_id;
                auto bit_offset = member.m_bit_offset;
                auto byte_offset = (member.m_bit_offset / 8);
                auto bits = member.m_bits;
                size_t size;
                if (bits != -1) {
                    size = member.m_bits / 8;
                } else {
                    size = ns.SizeOfType(tid);
                }
                std::cout << name << " / " <<
                    byte_offset << " / " <<
                    size << " / #" <<
                    tid << " / " <<
                    bit_offset << " / " <<
                    bits << std::endl;
            }
            std::cout << "-----------------------------------------------------------" << std::endl;
        }
        else if (rtype.m_flags & TF_UNION) {
            // union type
            std::cout << target << " is a union type, defined at " <<
                         type.m_location.str() << "." << std::endl;
            if (tid != rtid) {
                std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
            } else {
                std::cout << CrTabToSpace(ns.StringOfType(tid, "", true)) << ";" << std::endl;
            }
            std::cout << "[MEMBERS]" << std::endl;
            std::cout << "NAME / SIZE / #TYPE_ID" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            auto& ls = ns.LogStruct(rtype.m_sub_id);
            for (auto& member : ls.m_members) {
                auto name = member.m_name;
                if (name.empty()) {
                    name = "(no name)";
                }
                auto tid = member.m_type_id;
                size_t size = ns.SizeOfType(tid);
                std::cout << name << " / " <<
                    size << " / #" <<
                    tid << std::endl;
            }
            std::cout << "--------------------------------------------" << std::endl;
        }
        else if (rtype.m_flags & TF_POINTER) {
            // pointer type
            std::cout << target << " is a pointer type, defined at " <<
                         type.m_location.str() << "." << std::endl;
            std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
        } else if (rtype.m_flags & TF_FUNCTION) {
            // function type
            std::cout << target << " is a function type, defined at " <<
                         type.m_location.str() << "." << std::endl;
            std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
        } else {
            if (ns.IsIntegralType(rtid)) {
                // integral type
                if (ns.IsUnsignedType(rtid)) {
                    std::cout << target << " is an unsigned integral type, defined at " <<
                                 type.m_location.str() << "." << std::endl;
                    std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
                } else {
                    std::cout << target << " is a signed integral type, defined at " <<
                                 type.m_location.str() << "." << std::endl;
                    std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
                }
            } else if (ns.IsFloatingType(rtid)) {
                std::cout << target << " is a floating-point type, defined at " <<
                             type.m_location.str() << "." << std::endl;
                std::cout << "typedef " << CrTabToSpace(ns.StringOfType(tid, name, true)) << ";" << std::endl;
            } else {
                // other type
                std::cout << target << " is a type, defined at " <<
                             type.m_location.str() << "." << std::endl;
                std::cout << "typedef " << CrTabToSpace(ns.StringOfType(rtid, name, true)) << ";" << std::endl;
            }
        }
    }
    std::cout << "size: " << type.m_size << std::endl;
    std::cout << "alignment requirement: " << type.m_align << std::endl;
    return true;
}

bool IwDoVarOrFunc(CR_NameScope& ns, const std::string& target) {
    auto it = ns.MapNameToVarID().find(target);
    if (it != ns.MapNameToVarID().end()) {
        auto vid = it->second;
        auto& var = ns.LogVar(vid);
        auto& value = var.m_typed_value;
        auto tid = value.m_type_id;
        auto rtid = tid;
        if (tid != cr_invalid_id) {
            rtid = ns.ResolveAlias(tid);
        }
        if (ns.IsFuncType(rtid)) {
            // function
            std::cout << target << " is a function, defined at " <<
                var.m_location.str() << "." << std::endl;
            std::cout << ns.StringOfType(rtid, target, true) << ";" << std::endl;

            auto& rtype = ns.LogType(rtid);
            auto& func = ns.LogFunc(rtype.m_sub_id);
            if (rtype.m_flags & TF_CDECL) {
                std::cout << "Convention: __cdecl" << std::endl;
            } else if (rtype.m_flags & TF_STDCALL) {
                std::cout << "Convention: __stdcall" << std::endl;
            } else if (rtype.m_flags & TF_FASTCALL) {
                std::cout << "Convention: __fastcall" << std::endl;
            }

            std::cout << "The type ID of return value: #" << func.m_return_type << std::endl;
            std::cout << "[PARAMETERS]" << std::endl;
            std::cout << "ORDINAL / NAME / #TYPE_ID" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            int i = 1;
            for (auto& param : func.m_params) {
                std::cout << i << " / " << param.m_name << " / #" << param.m_type_id << std::endl;
                ++i;
            }
        } else {
            if (var.m_is_macro) {
                assert(rtid != cr_invalid_id);
                if (var.m_location.m_file == "(predefined)") {
                    // predefined macro constant
                    std::cout << target << " is a predefined macro constant." << std::endl;
                    std::cout << ns.StringOfType(tid, target, false) << " = " <<
                        value.m_text << value.m_extra << ";" << std::endl;
                } else {
                    // macro constant
                    std::cout << target << " is a macro constant, defined at " <<
                        var.m_location.str() << "." << std::endl;
                    if (ns.IsPointerType(tid) && value.m_text.size() && value.m_text[0] != '\"') {
                        std::cout << ns.StringOfType(tid, target, false) << " = (" <<
                            ns.StringOfType(tid, "") << ")" <<
                            ns.StringFromValue(value) << ";" << std::endl;
                    } else {
                        std::cout << ns.StringOfType(tid, target, false) << " = " <<
                            ns.StringFromValue(value) << ";" << std::endl;
                    }
                }
                auto& type = ns.LogType(rtid);
                std::cout << "size: " << type.m_size << std::endl;
                std::cout << "alignment requirement: " << type.m_align << std::endl;
            } else {
                if (rtid != cr_invalid_id) {
                    // variable with value
                    std::cout << target << " is a variable, defined at " <<
                        var.m_location.str() << "." << std::endl;
                    std::cout << ns.StringOfType(tid, target, false) << " = " <<
                                 ns.StringFromValue(value) << ";" << std::endl;
                    auto& type = ns.LogType(rtid);
                    std::cout << "size: " << type.m_size << std::endl;
                    std::cout << "alignment requirement: " << type.m_align << std::endl;
                } else {
                    // variable without value
                    std::cout << target << " is a variable without value, defined at " <<
                        var.m_location.str() << "." << std::endl;
                    std::cout << ns.StringOfType(tid, target, false) << ";" << std::endl;
                    auto& type = ns.LogType(rtid);
                    std::cout << "size: " << type.m_size << std::endl;
                    std::cout << "alignment requirement: " << type.m_align << std::endl;
                }
            }
        }
        return true;
    }
    return false;
}

bool IwJustDoIt(CR_NameScope& ns, const std::string& target) {
    bool ret = false;
    // #type_id
    if (target[0] == '#') {
        auto number = target.substr(1);
        auto tid = std::stoul(number);
        auto name = ns.NameFromTypeID(tid);
        return IwDoType(ns, tid, target, name);
    }
    // type
    {
        auto it = ns.MapNameToTypeID().find(target);
        if (it != ns.MapNameToTypeID().end()) {
            auto tid = it->second;
            ret = ret || IwDoType(ns, tid, target, target);
        }
    }
    // variable or function
    {
        ret = ret || IwDoVarOrFunc(ns, target);
    }
    // name alias
    {
        auto it = ns.MapNameToName().find(target);
        if (it != ns.MapNameToName().end()) {
            auto name2name = it->second;
            std::cout << target << " is an alias macro of " << 
                name2name.m_to << ", defined at " <<
                name2name.m_location.str() << "." << std::endl;
            ret = true;
        }
    }
    if (!ret) {
        std::cout << "I don't know." << std::endl;
    }
    return ret;
}

bool IwJustDoIt(
    const std::string& prefix, const std::string& suffix,
    const std::string& target)
{
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

    std::cout << "Loading data..." << std::endl;
    if (!ns.LoadFromFiles(prefix, suffix)) {
        std::cerr << "ERROR: cannot load data" << std::endl;
        return false;
    }
    std::cout << "Loaded." << std::endl;

    if (target.size()) {
        return IwJustDoIt(ns, target);
    } else {
        std::cout << "You are welcome!" << std::endl;
        std::cout << "Enter 'quit' to quit." << std::endl;
        std::string line;
        for (;;) {
            std::cout << std::endl;
            std::cout << "Enter name of type, function or constant: ";
            std::getline(std::cin, line);
            katahiromz::trim(line);
            do {
                ;
            } while (katahiromz::replace_string(line, "  ", " "));
            if (line == "quit" || line == "Quit" || line == "QUIT") {
                std::cout << "See you!" << std::endl;
                break;
            }
            IwJustDoIt(ns, line);
        }
        return true;
    }

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

    std::string target;
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
        } else if (argv[i][0] == '-' || argv[i][0] == '/') {
            std::cerr << "ERROR: Invalid option '" << argv[i] <<
                         "'." << std::endl;
            return 1;
        } else {
            if (target.empty()) {
                target = argv[i];
            } else {
                target += " ";
                target += argv[i];
            }
        }
    }

    if (show_help) {
        IwShowHelp();
        return 0;
    }

    if (show_version) {
        IwShowVersion();
        return 0;
    }

    if (target.empty()) {
        IwShowLogo();
    }
    IwJustDoIt(prefix, suffix, target);

    return 0;
}
