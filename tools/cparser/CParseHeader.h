////////////////////////////////////////////////////////////////////////////
// CParseHeader.h
// Copyright (C) 2014-2015 Katayama Hirofumi MZ.  All rights reserved.
////////////////////////////////////////////////////////////////////////////
// This file is part of CodeReverse. See file ReadMe.txt and License.txt.
////////////////////////////////////////////////////////////////////////////

#ifndef CPARSEHEADER_H_
#define CPARSEHEADER_H_

#include <istream>          // for std::ifstream
#include <fstream>          // for std::ifstream
#include <iterator>         // for std::istreambuf_iterator

#include "CParser.h"        // for cparser::Parser

namespace cparser
{
    typedef std::istreambuf_iterator<char>  scanner_iterator;
    typedef std::string::iterator           str_iterator;
    typedef TokenNode<Token>                node_type;
    typedef std::vector<node_type>          node_container;
    typedef node_container::iterator        node_iterator;
}

#include "CLexer.h"       // for cparser::Lexer
#include "CActions.h"    // for cparser::Actions

namespace cparser
{
    inline bool parse(
        shared_ptr<CR_ErrorInfo> error_info, shared_ptr<TransUnit>& tu,
        scanner_iterator begin, scanner_iterator end,
        bool is_64bit = false)
    {
        using namespace cparser;

        Actions as;
        Lexer lexer(error_info, is_64bit);

        std::vector<CR_TokenNode> infos;
        lexer.just_do_it(infos, begin, end);
        #if 0
            std::printf("\n#2\n");
            lexer.show_tokens(infos.begin(), infos.end());
            std::printf("\n--------------\n");
            fflush(stdout);
        #endif

        Parser<shared_ptr<Node>, Actions> parser(as);
        auto infos_end = infos.end();
        for (auto it = infos.begin(); it != infos_end; ++it) {
            if (parser.post(it->m_token, make_shared<CR_TokenNode>(*it))) {
                if (parser.error()) {
                    // show around tokens
                    std::string around;
                    int count = 50;
                    auto it_save = it;
                    for (int i = 0; i < count / 2; ++i) {
                        if (infos.begin() != it)
                            --it;
                        else
                            break;
                    }
                    for (int i = 0; i < count; ++i) {
                        if (infos_end != it) {
                            around += lexer.node_to_string(*it);
                            around += ' ';
                            ++it;
                        }
                        else
                            break;
                    }
                    error_info->add_error(
                        it_save->m_location,
                        "syntax error near " + lexer.node_to_string(*it_save) +
                        "\n" + "around: " + around
                    );
                    error_info->emit_all();
                    return false;
                }
                break;
            }
        }

        shared_ptr<Node> node;
        if (parser.accept(node)) {
            std::cerr << "Parser accepted!" << std::endl;
            tu = static_pointer_cast<TransUnit, Node>(node);
            return true;
        }

        return false;
    }

    inline bool parse_expression(
        shared_ptr<CR_ErrorInfo> error_info, shared_ptr<Expr>& expr,
        std::string& strExpr, shared_ptr<TypeNames>& type_names,
        bool is_64bit = false)
    {
        using namespace cparser;
        str_iterator begin = strExpr.begin();
        str_iterator end = strExpr.end();

        Actions as;
        Lexer lexer(error_info, is_64bit);
        lexer.m_type_names = type_names;

        std::vector<CR_TokenNode> infos;
        lexer.just_do_it2(infos, T_EXPRESSION, begin, end);

        Parser<shared_ptr<Node>, Actions> parser(as);
        auto infos_end = infos.end();
        for (auto it = infos.begin(); it != infos_end; ++it) {
            if (parser.post(it->m_token, make_shared<CR_TokenNode>(*it))) {
                if (parser.error()) {
                    #if 0
                        std::printf("#1\n");
                        lexer.show_tokens(infos.begin(), infos.end());
                        std::printf("\n--------------\n");
                    #endif
                    return false;
                }
                break;
            }
        }

        #ifdef DEEPDEBUG
            std::printf("#1\n");
            lexer.show_tokens(infos.begin(), infos.end());
            std::printf("\n--------------\n");
        #endif

        shared_ptr<Node> node;
        if (parser.accept(node)) {
            shared_ptr<TransUnit> tu;
            tu = static_pointer_cast<TransUnit, Node>(node);
            expr = tu->m_expr;
            return true;
        } else {
            #if 0
                std::printf("#2\n");
                lexer.show_tokens(infos.begin(), infos.end());
                std::printf("\n--------------\n");
            #endif
        }

        return false;
    }

    inline bool parse_type(
        shared_ptr<CR_ErrorInfo> error_info, shared_ptr<TypeName>& type_name,
        std::string& strType, shared_ptr<TypeNames>& type_names,
        bool is_64bit = false)
    {
        using namespace cparser;
        str_iterator begin = strType.begin();
        str_iterator end = strType.end();

        Actions as;
        Lexer lexer(error_info, is_64bit);
        lexer.m_type_names = type_names;

        std::vector<CR_TokenNode> infos;
        lexer.just_do_it2(infos, T_TYPE, begin, end);

        Parser<shared_ptr<Node>, Actions> parser(as);
        auto infos_end = infos.end();
        for (auto it = infos.begin(); it != infos_end; ++it) {
            if (parser.post(it->m_token, make_shared<CR_TokenNode>(*it))) {
                if (parser.error()) {
                    #if 0
                        std::printf("#1\n");
                        lexer.show_tokens(infos.begin(), infos.end());
                        std::printf("\n--------------\n");
                    #endif
                    return false;
                }
                break;
            }
        }

        shared_ptr<Node> node;
        if (parser.accept(node)) {
            shared_ptr<TransUnit> tu;
            tu = static_pointer_cast<TransUnit, Node>(node);
            type_name = tu->m_type_name;
            return true;
        } else {
            #if 0
                std::printf("#2\n");
                lexer.show_tokens(infos.begin(), infos.end());
                std::printf("\n--------------\n");
            #endif
        }

        return false;
    }

    inline bool parse_file(
        shared_ptr<CR_ErrorInfo> error_info, shared_ptr<TransUnit>& ts,
        const char *filename, bool is_64bit = false)
    {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::istreambuf_iterator<char> begin(file), end;
            bool ok = parse(error_info, ts, begin, end, is_64bit);
            file.close();
            return ok;
        }
        return false;
    }
} // namespace cparser

#endif  // ndef CPARSEHEADER_H_
