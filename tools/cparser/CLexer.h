////////////////////////////////////////////////////////////////////////////
// CLexer.h
// Copyright (C) 2014-2015 Katayama Hirofumi MZ.  All rights reserved.
////////////////////////////////////////////////////////////////////////////
// This file is part of CodeReverse. See file ReadMe.txt and License.txt.
////////////////////////////////////////////////////////////////////////////

#ifndef CLEXER_H_
#define CLEXER_H_

namespace cparser
{
    //
    // Packing
    //
    class Packing {
    public:
        Packing(int pack = 8, int default_packing = 8) :
            m_pack(pack), m_default_packing(default_packing) { }

        void push(int pack) {
            assert(pack == 1 || pack == 2 || pack == 4 || pack == 8 || pack == 16);
            m_packs.push_back(m_pack);
            m_idents.emplace_back("");
            m_pack = pack;
        }

        void pop(int pack) {
            assert(pack == 1 || pack == 2 || pack == 4 || pack == 8 || pack == 16);
            pop();
            m_pack = pack;
        }

        void pop() {
            assert(m_packs.size());
            m_pack = m_packs.back();
            m_packs.pop_back();
            m_idents.pop_back();
        }

        void push(const std::string& ident) {
            m_packs.push_back(m_pack);
            m_idents.emplace_back(ident);
        }

        bool pop(const std::string& ident) {
            while (m_packs.size()) {
                assert(m_idents.size());
                if (m_idents.back() == ident) {
                    pop();
                    return true;
                }
                pop();
            }
            set(m_default_packing);
            return false;
        }

        int  get() const        { return m_pack; }
        void set(int pack)      { m_pack = pack; }
        operator int() const    { return get(); }

              int& default_packing()        { return m_default_packing; }
        const int& default_packing() const  { return m_default_packing; }

    protected:
        int                         m_pack;
        int                         m_default_packing;
        std::vector<int>            m_packs;
        std::vector<std::string>    m_idents;
    }; // Packing

    //
    // LexerBase
    //
    class LexerBase {
    public:
        LexerBase(scanner_iterator begin, scanner_iterator end) :
            m_current(begin), m_end(end) { }

        char getch() {
            char c;
            if (is_eof()) {
                c = -1;
            } else {
                c = *m_current++;
            }
            return c;
        } // getch

        bool is_eof() const {
            return m_current == m_end || *m_current == -1;
        }

              Packing& packing()       { return m_packing; }
        const Packing& packing() const { return m_packing; }

              int& default_packing()        { return packing().default_packing(); }
        const int& default_packing() const  { return packing().default_packing(); }

    protected:
        scanner_iterator    m_current;
        scanner_iterator    m_end;
        Packing             m_packing;
    public:
        CR_Location         m_location;
    };

    //
    // LexerBase
    //
    class LexerBase2 {
    public:
        LexerBase2(str_iterator begin, str_iterator end) :
            m_current(begin), m_end(end) { }

        char getch() {
            char c;
            if (is_eof()) {
                c = -1;
            } else {
                c = *m_current++;
            }
            return c;
        } // getch

        bool is_eof() const {
            return m_current == m_end || *m_current == -1;
        }

              Packing& packing()       { return m_packing; }
        const Packing& packing() const { return m_packing; }

              int& default_packing()        { return packing().default_packing(); }
        const int& default_packing() const  { return packing().default_packing(); }

    protected:
        str_iterator        m_current;
        str_iterator        m_end;
        Packing             m_packing;
    public:
        CR_Location         m_location;
    };

    //
    // TypeNames
    //
    typedef std::unordered_set<std::string> TypeNames;

    //
    // Lexer
    //
    class Lexer {
    public:
        Lexer(shared_ptr<CR_ErrorInfo> error_info, bool is_64bit = false) :
            m_error_info(error_info), m_is_64bit(is_64bit),
            m_in_c_comment(false), m_in_cxx_comment(false),
            m_type_names(make_shared<TypeNames>())
        {
            init_symbol_table();
        }

        bool is_in_block_comment() const { return m_in_c_comment; }
        bool is_in_line_comment() const { return m_in_cxx_comment; }

        void just_do_it(node_container& infos,
                        scanner_iterator begin, scanner_iterator end);
        void just_do_it2(node_container& infos, Token token,
                         str_iterator begin, str_iterator end);

        void show_tokens(node_iterator begin, node_iterator end) const {
            for (auto it = begin; it != end; ++it) {
                printf("%s ", node_to_string(*it).data());
            }
        }

        std::string node_to_string(const node_type& node) const;

        void newline(node_container& infos) {
            infos.emplace_back(T_NEWLINE, "\\n");
        }

        void skip_block_comment(LexerBase& base, node_container& infos);
        void skip_block_comment2(LexerBase2& base, node_container& infos);
        void skip_line_comment(LexerBase& base, node_container& infos);
        void skip_line_comment2(LexerBase2& base, node_container& infos);

        std::string get_line(LexerBase& base);
        std::string get_line2(LexerBase2& base);
        bool get_tokens(LexerBase& base, node_container& infos);
        bool get_tokens2(LexerBase2& base, node_container& infos);
        void do_line(const std::string& line, node_container& infos);
        bool token_pattern_match(
            LexerBase& base, node_iterator it, node_iterator end,
            const std::vector<Token>& tokens) const;

        void skip_paren_block(node_iterator& begin, node_iterator end);

    protected:
        //
        // resynth
        //
        void resynth(LexerBase& base, node_container& c);

        void resynth1(LexerBase& base, node_container& c);
        void resynth2(LexerBase& base, node_container& c);
        void resynth3(node_container& c);
        void resynth4(node_container& c);
        void resynth5(node_iterator begin, node_iterator end);

        node_iterator
        resynth_typedef(node_iterator begin, node_iterator end);

        node_iterator resynth_parameter_list(
            node_iterator begin, node_iterator end);

        void resynth6(node_container& c);
        void resynth7(node_iterator begin, node_iterator end);

        void resynth(LexerBase2& base, node_container& c);
        void resynth1(LexerBase2& base, node_container& c);
        void resynth2(LexerBase2& base, node_container& c);

        Token parse_identifier(const std::string& text) const;

        CR_ErrorInfo::Type
        parse_pragma(LexerBase& base, node_iterator it, node_iterator end);

        CR_ErrorInfo::Type
        parse_pack(LexerBase& base, node_iterator it, node_iterator end);

    protected:
        shared_ptr<CR_ErrorInfo>    m_error_info;
        bool                        m_is_64bit;
        bool                        m_in_c_comment;
        bool                        m_in_cxx_comment;
        std::unordered_map<std::string, Token>      m_symbol_table;

    public:
        shared_ptr<TypeNames>                       m_type_names;

        //
        // pragma
        //
        void lib(const std::string str) { }

        void linker(const std::string str) { }

        void add_notice(const CR_Location& location, const std::string& text) {
            m_error_info->add_notice(location, text);
        }
        void add_warning(const CR_Location& location, const std::string& text) {
            m_error_info->add_warning(location, text);
        }
        void add_error(const CR_Location& location, const std::string& text) {
            m_error_info->add_error(location, text);
        }
        void add_message(CR_ErrorInfo::Type type, const CR_Location& location,
                         const std::string& text)
        {
            m_error_info->add_message(type, location, text);
        }

        void message(const CR_Location& location, const std::string& text) {
            add_notice(location, text);
        }

        void init_symbol_table();

    private:
        // NOTE: Lexer is not copyable.
        Lexer(const Lexer&) = delete;
        Lexer& operator=(const Lexer&) = delete;
    }; // class Lexer
} // namespace cparser

#endif  // ndef CLEXER_H_
