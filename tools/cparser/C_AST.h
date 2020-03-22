////////////////////////////////////////////////////////////////////////////
// C_AST.h
// Copyright (C) 2014-2015 Katayama Hirofumi MZ.  All rights reserved.
////////////////////////////////////////////////////////////////////////////
// This file is part of CodeReverse. See file ReadMe.txt and License.txt.
////////////////////////////////////////////////////////////////////////////

#ifndef CPARSER_AST_H_
#define CPARSER_AST_H_

namespace cparser
{
    struct Node;
    struct Declor;
    struct DeclorList;
    struct AsmOperand;
    struct AsmOperands;
    struct AsmSpec;
    struct AsmBlock;
    struct Decl;
    struct DeclList;
    struct ExtDecl;
    struct TransUnit;
    struct AtomicTypeSpec;
    struct TypeSpec;
    struct TypeQual;
    struct TypeQualList;
    struct StorClsSpec;
    struct FuncSpec;
    struct DeclSpecs;
    struct Pointers;
    struct Enumor;
    struct EnumorList;
    struct AstCom;
    struct ParamList;
    struct IdentList;
    struct Initer;
    struct IniterList;
    struct TypeName;
    struct Expr;
    struct AssignExpr;
    struct CondExpr;
    struct LogOrExpr;
    struct LogAndExpr;
    struct InclOrExpr;
    struct ExclOrExpr;
    struct AndExpr;
    struct EqualExpr;
    struct RelExpr;
    struct ShiftExpr;
    struct AddExpr;
    struct MulExpr;
    struct CastExpr;
    struct UnaryExpr;
    struct PostfixExpr;
    struct PrimExpr;
    struct GeneSel;
    struct GeneAssoc;
    struct GeneAssocList;
    struct ArgExprList;
    struct Stmt;
    struct StmtList;
    struct AlignSpec;
    struct StaticAssertDecl;
    struct LabeledStmt;
    struct ExprStmt;
    struct CompStmt;
    struct SelStmt;
    struct IterStmt;
    struct JumpStmt;

    //
    // Node
    //
    struct Node {
        Node() { }
        Node(const CR_Location& location) : m_location(location) { }
        virtual ~Node() { }

        CR_Location  m_location;
    };

    struct Declor : Node {
        Declor() : m_flags(0) { }
        CR_TypeFlags            m_flags;
        enum {
            TYPEDEF_TAG, ARRAY, FUNCTION, IDENTIFIER, BITS, POINTERS
        } m_declor_type;
        std::string             m_name;
        shared_ptr<Declor>      m_declor;       // can be NULL
        shared_ptr<CondExpr>    m_const_expr;   // can be NULL
        shared_ptr<ParamList>   m_param_list;   // can be NULL
        shared_ptr<Initer>      m_initer;       // can be NULL
        shared_ptr<Pointers>    m_pointers;     // can be NULL
    };

    struct DeclorList : Node, std::vector<shared_ptr<Declor>> {
    };

    struct AsmOperand : Node {
        enum {
            STRING, IDENTIFIER, COMMA, COLON, PAREN, BRACKET
        } m_operand_type;
        std::string                 m_text;
        shared_ptr<Expr>            m_expr;
    };

    struct AsmOperands : Node, std::vector<shared_ptr<AsmOperand>> {
    };

    struct AsmSpec : Node {
        shared_ptr<TypeQualList>    m_type_qual_list;
        shared_ptr<AsmOperands>     m_asm_operands;
    };

    struct AsmBlock : Node {
        shared_ptr<AsmOperands> m_asm_operands;
    };

    struct Decl : Node {
        enum {
            FUNCTION, TYPEDEF, DECLORLIST, SINGLE, STATIC_ASSERT,
            ASMSPEC, ASMBLOCK, PARAM
        } m_decl_type;
        shared_ptr<DeclSpecs>           m_decl_specs;           // can be NULL
        shared_ptr<DeclorList>          m_declor_list;          // can be NULL
        shared_ptr<DeclList>            m_decl_list;            // can be NULL
        shared_ptr<StaticAssertDecl>    m_static_assert_decl;   // can be NULL
        shared_ptr<CompStmt>            m_comp_stmt;            // can be NULL
        shared_ptr<AsmSpec>             m_asm_spec;             // can be NULL
        shared_ptr<AsmBlock>            m_asm_block;            // can be NULL
        shared_ptr<AlignSpec>           m_align_spec;           // can be NULL
        std::string                     m_constant;
    };

    struct DeclList : Node, std::vector<shared_ptr<Decl>> {
    };

    struct ExtDecl : Node {
        shared_ptr<Decl> m_decl;    // can be NULL
    };

    struct TransUnit : Node, std::vector<shared_ptr<Decl>> {
        shared_ptr<Expr>        m_expr;
        shared_ptr<TypeName>    m_type_name;
    };

    struct AtomicTypeSpec : Node {
        shared_ptr<TypeName> m_type_name;
    };

    struct TypeSpec : Node {
        CR_TypeFlags                m_flag;
        int                         m_pack;
        // struct/union/enum tag name or typedef name
        std::string                 m_name;
        shared_ptr<DeclList>        m_decl_list;            // for struct, union or enum
        shared_ptr<EnumorList>      m_enumor_list;
        shared_ptr<AtomicTypeSpec>  m_atomic_type_spec;
        shared_ptr<AlignSpec>       m_align_spec;           // can be NULL
        TypeSpec() : m_flag(0), m_pack(8) { }
    };

    struct TypeQual : Node {
        CR_TypeFlags                m_flag;
        TypeQual() : m_flag(0) { }
    };

    struct TypeQualList : Node {
        CR_TypeFlags                m_flags;
        TypeQualList() : m_flags(0) { }
    };

    struct StorClsSpec : Node {
        enum {
            AUTO, EXTERN, REGISTER, STATIC, THREADLOCAL
        } m_scs_type;
        StorClsSpec() { }
    };

    struct FuncSpec : Node {
        enum {
            INLINE, DOFORCEINLINE, NORETURN
        } m_func_spec_type;
        FuncSpec() { }
    };

    struct DeclSpecs : Node {
        enum {
            STORCLSSPEC, FUNCSPEC, TYPESPEC, TYPEQUAL
        } m_spec_type;
        shared_ptr<StorClsSpec> m_stor_cls_spec;    // can be NULL
        shared_ptr<FuncSpec>    m_func_spec;        // can be NULL
        shared_ptr<DeclSpecs>   m_decl_specs;       // can be NULL
        shared_ptr<TypeSpec>    m_type_spec;        // can be NULL
        shared_ptr<TypeQual>    m_type_qual;        // can be NULL
    };

    struct Pointers : Node, std::vector<shared_ptr<AstCom>> {
    };

    struct Enumor : Node {
        std::string             m_name;
        shared_ptr<CondExpr>    m_const_expr;
    };

    struct EnumorList : Node, std::vector<shared_ptr<Enumor>> {
    };

    struct AstCom : Node {
        CR_TypeFlags m_flags;
        AstCom() : m_flags(0) { }
    };

    struct ParamList : Node, std::vector<shared_ptr<Decl>> {
        bool m_ellipsis;
        ParamList() : m_ellipsis(false) { }
    };

    struct IdentList : Node, std::vector<std::string> {
    };

    struct Initer : Node {
        enum {
            SIMPLE, COMPOUND
        } m_initer_type;
        shared_ptr<AssignExpr> m_assign_expr;
        shared_ptr<IniterList> m_initer_list;
    };

    struct IniterList : Node, std::vector<shared_ptr<Initer>> {
    };

    struct TypeName : Node {
        shared_ptr<DeclSpecs>   m_decl_specs;
        shared_ptr<Declor>      m_declor;   // can be NULL
    };

    struct Expr : Node, std::vector<shared_ptr<AssignExpr>> {
    };

    struct AssignExpr : Node {
        enum {
            COND, ASSIGN, MUL, DIV, MOD, ADD, SUB, 
            L_SHIFT, R_SHIFT, AND, XOR, OR
        } m_assign_type;
        shared_ptr<CondExpr>    m_cond_expr;
        shared_ptr<UnaryExpr>   m_unary_expr;
        shared_ptr<AssignExpr>  m_assign_expr;
    };

    struct CondExpr : Node {
        enum {
            SINGLE, QUESTION
        } m_cond_type;
        shared_ptr<LogOrExpr>   m_log_or_expr;
        shared_ptr<Expr>        m_expr;
        shared_ptr<CondExpr>    m_cond_expr;
    };

    struct LogOrExpr : Node, std::vector<shared_ptr<LogAndExpr>> {
    };

    struct LogAndExpr : Node, std::vector<shared_ptr<InclOrExpr>> {
    };

    struct InclOrExpr : Node, std::vector<shared_ptr<ExclOrExpr>> {
    };

    struct ExclOrExpr : Node, std::vector<shared_ptr<AndExpr>> {
    };

    struct AndExpr : Node, std::vector<shared_ptr<EqualExpr>> {
    };

    struct EqualExpr : Node {
        enum {
            SINGLE, EQUAL, NE
        } m_equal_type;
        shared_ptr<EqualExpr>   m_equal_expr;
        shared_ptr<RelExpr>     m_rel_expr;
    };

    struct RelExpr : Node {
        enum {
            SINGLE, LT, GT, LE, GE
        } m_rel_type;
        shared_ptr<RelExpr>     m_rel_expr;
        shared_ptr<ShiftExpr>   m_shift_expr;
    };

    struct ShiftExpr : Node {
        enum {
            SINGLE, L_SHIFT, R_SHIFT
        } m_shift_type;
        shared_ptr<ShiftExpr>   m_shift_expr;
        shared_ptr<AddExpr>     m_add_expr;
    };

    struct AddExpr : Node {
        enum {
            SINGLE, PLUS, MINUS
        } m_add_type;
        shared_ptr<AddExpr>     m_add_expr;
        shared_ptr<MulExpr>     m_mul_expr;
    };

    struct MulExpr : Node {
        enum {
            SINGLE, ASTERISK, SLASH, PERCENT
        } m_mul_type;
        shared_ptr<MulExpr>     m_mul_expr;
        shared_ptr<CastExpr>    m_cast_expr;
    };

    struct CastExpr : Node {
        enum {
            UNARY, INITERLIST, CAST
        } m_cast_type;
        shared_ptr<UnaryExpr>   m_unary_expr;
        shared_ptr<TypeName>    m_type_name;
        shared_ptr<CastExpr>    m_cast_expr;
        shared_ptr<IniterList>  m_initer_list;
    };

    struct UnaryExpr : Node {
        enum {
            SINGLE, INC, DEC, ADDRESS, ASTERISK, PLUS, MINUS,
            BITWISE_NOT, NOT, SIZEOF1, SIZEOF2, ALIGNOF
        } m_unary_type;
        shared_ptr<PostfixExpr> m_postfix_expr;
        shared_ptr<UnaryExpr>   m_unary_expr;
        shared_ptr<CastExpr>    m_cast_expr;
        shared_ptr<TypeName>    m_type_name;
    };

    struct PostfixExpr : Node {
        enum {
            SINGLE, ARRAYITEM, FUNCCALL1, FUNCCALL2, DOT,
            ARROW, INC, DEC
        } m_postfix_type;
        shared_ptr<PostfixExpr> m_postfix_expr;
        shared_ptr<PrimExpr>    m_prim_expr;
        std::string             m_text;
        shared_ptr<Expr>        m_expr;
    };

    struct PrimExpr : Node {
        enum {
            IDENTIFIER, I_CONSTANT, F_CONSTANT, STRING, PAREN, SELECTION
        } m_prim_type;
        std::string         m_text;
        std::string         m_extra;
        shared_ptr<Expr>    m_expr;
        shared_ptr<GeneSel> m_gen_sel;
        CR_TypeFlags        m_flags;
    };

    struct GeneSel : Node {
        shared_ptr<AssignExpr>      m_assign_expr;
        shared_ptr<GeneAssocList>   m_gene_assoc_list;
    };

    struct GeneAssoc : Node {
        enum {
            NONDEFAULT, DEFAULT
        } m_gene_assoc_type;
        shared_ptr<TypeName>    m_type_name;
        shared_ptr<AssignExpr>  m_assign_expr;
    };

    struct GeneAssocList : Node, std::vector<shared_ptr<GeneAssoc>> {
    };

    struct ArgExprList : Node, std::vector<shared_ptr<AssignExpr>> {
    };

    struct LabeledStmt : Node {
        enum {
            LABEL, CASE, DEFAULT
        } m_labeled_type;
        std::string             m_label;
        shared_ptr<CondExpr>    m_const_expr;
        shared_ptr<Stmt>        m_stmt;
    };
    
    struct ExprStmt : Node {
        shared_ptr<Expr> m_expr;
    };
    
    struct CompStmt : Node {
        shared_ptr<DeclList> m_decl_list;
        shared_ptr<StmtList> m_stmt_list;
    };
    
    struct SelStmt : Node {
        enum {
            IF_THEN_ELSE, IF_THEN, SWITCH
        } m_sel_type;
        shared_ptr<Expr> m_expr;
        shared_ptr<Stmt> m_then;
        shared_ptr<Stmt> m_else;
    };
    
    struct IterStmt : Node {
        enum {
            WHILE, DO_WHILE, FOR
        } m_iter_type;
        shared_ptr<Expr> m_expr1;   // can be NULL
        shared_ptr<Expr> m_expr2;   // can be NULL
        shared_ptr<Expr> m_expr3;   // can be NULL
        shared_ptr<Stmt> m_stmt;
    };
    
    struct JumpStmt : Node {
        enum {
            GOTO, CONTINUE, BREAK, RETURN_VOID, RETURN_EXPR
        } m_jump_type;
        std::string         m_label;
        shared_ptr<Expr>    m_expr;
    };
    
    struct Stmt : Node {
        enum {
            LABELED, EXPR, COMP, SEL, ITER, JUMP
        } m_stmt_type;
        shared_ptr<LabeledStmt>     m_labeled_stmt;
        shared_ptr<ExprStmt>        m_expr_stmt;
        shared_ptr<CompStmt>        m_comp_stmt;
        shared_ptr<SelStmt>         m_sel_stmt;
        shared_ptr<IterStmt>        m_iter_stmt;
        shared_ptr<JumpStmt>        m_jump_stmt;
    };

    struct StmtList : Node, std::vector<shared_ptr<Stmt>> {
    };

    struct AlignSpec : Node {
        enum {
            TYPENAME, CONSTEXPR
        } m_align_spec_type;
        shared_ptr<TypeName>    m_type_name;
        shared_ptr<CondExpr>    m_const_expr;
    };

    struct StaticAssertDecl : Node {
        shared_ptr<CondExpr>    m_const_expr;
        std::string             m_str;
        CR_Location             m_location;
    };

    //
    // TokenNode<TokenType>
    //
    template <typename TokenType>
    struct TokenNode : Node {
        typedef TokenType token_type;

        token_type      m_token;
        std::string     m_str;
        std::string     m_extra;
        int             m_pack;
        CR_TypeFlags    m_flags;

    public:
        TokenNode() : m_pack(8), m_flags(0) { }

        TokenNode(token_type token) :
            m_token(token), m_pack(8), m_flags(0) { }

        TokenNode(token_type token, const std::string& str) :
            m_token(token), m_str(str), m_pack(8), m_flags(0) { }

        TokenNode(token_type token, 
                  const std::string& str, const std::string& extra) :
            m_token(token), m_str(str),
            m_extra(extra), m_pack(8), m_flags(0) { }

        TokenNode(token_type token,  const std::string& str,
                  const std::string& extra, CR_TypeFlags flags) :
            m_token(token), m_str(str), m_extra(extra),
            m_pack(8), m_flags(flags) { }

        void set_token(token_type token) {
            m_token = token;
        }
    }; // struct TokenNode

    //
    // CR_TokenNode
    //
    #define CR_TokenNode TokenNode<Token>
} // namespace cparser

#endif  // ndef CPARSER_AST_H_
