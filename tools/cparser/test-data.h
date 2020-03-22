#if 0
    #define MAX_LINKID_TEXT     48
    #define L_MAX_URL_LENGTH    (2048 + 32 + sizeof("://"))

    typedef struct tagLITEM
    {
        int         mask ;
        int         iLink ;
        int         state ;
        int         stateMask ;
        unsigned short szID[MAX_LINKID_TEXT] ;
        unsigned short szUrl[L_MAX_URL_LENGTH] ;
    } LITEM, * PLITEM ;

    #define MAX_LANA       254

    typedef struct _LANA_ENUM {
        unsigned char length;
        unsigned char lana[MAX_LANA+1];
    } LANA_ENUM, *PLANA_ENUM;

    #define TEST MAX_LANA + 1

    #if defined(UNICODE)
    # define __MINGW_NAME_AW(func) func##W
    #else
    # define __MINGW_NAME_AW(func) func##A
    #endif

    int lstrlenA(const char *str);
    int lstrlenW(const unsigned short *str);

    #define lstrlen __MINGW_NAME_AW(lstrlen)

    #define CCSIZEOF_STRUCT(structname, member)  (((int)((char *)(&((structname*)0)->member) - ((char *)((structname*)0)))) + sizeof(((structname*)0)->member))

    #define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                    ((unsigned long)(unsigned char)(ch0) | ((unsigned long)(unsigned char)(ch1) << 8) |   \
                    ((unsigned long)(unsigned char)(ch2) << 16) | ((unsigned long)(unsigned char)(ch3) << 24 ))
    #define mmioFOURCC(ch0, ch1, ch2, ch3)  MAKEFOURCC(ch0, ch1, ch2, ch3)
    #define ACMDRIVERDETAILS_FCCCOMP_UNDEFINED  mmioFOURCC('\0', '\0', '\0', '\0')

    #define _HUGE_ENUF  1e+300  /* _HUGE_ENUF*_HUGE_ENUF must overflow */

    #define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))  /* causes warning C4756: overflow in constant arithmetic (by design) */
    #define NAN        ((float)(INFINITY * 0.0F))

    static const unsigned short c_szMiracast[] = L"Miracast";
    static const unsigned short c_szzWiFiDirectServices[] = L"Miracast\0";

    enum {
        ProcThreadAttributeProtectionLevel = 11
    };

    #define PROC_THREAD_ATTRIBUTE_NUMBER    0x0000FFFF
    #define PROC_THREAD_ATTRIBUTE_THREAD    0x00010000  // Attribute may be used with thread creation
    #define PROC_THREAD_ATTRIBUTE_INPUT     0x00020000  // Attribute is input only
    #define PROC_THREAD_ATTRIBUTE_ADDITIVE  0x00040000  // Attribute may be "accumulated," e.g. bitmasks, counters, etc.

    #define ProcThreadAttributeValue(Number, Thread, Input, Additive) \
        (((Number) & PROC_THREAD_ATTRIBUTE_NUMBER) | \
         ((Thread != 0) ? PROC_THREAD_ATTRIBUTE_THREAD : 0) | \
         ((Input != 0) ? PROC_THREAD_ATTRIBUTE_INPUT : 0) | \
         ((Additive != 0) ? PROC_THREAD_ATTRIBUTE_ADDITIVE : 0))

    #define PROC_THREAD_ATTRIBUTE_PROTECTION_LEVEL \
        ProcThreadAttributeValue (ProcThreadAttributeProtectionLevel, 0, 1, 0)

    #define TOUCHPREDICTIONPARAMETERS_DEFAULT_RLS_EXPO_SMOOTH_ALPHA 0.99f

    typedef long LONG;

    const LONG long_constant = 123456;

    #define LONG_CONSTANT 123456L

    typedef const int * const constant_pointer_type;

    unsigned short wstr[10] = {1, 2, 3, 4, 5, 7};
    const int const_int_array[2] = {1, 2};
    const unsigned short *pwsz = L"1234";
    const char *psz = L"1234";
    const char sz[] = "123";

    const int * const constant_pointer = (void *)0;

    typedef struct _GUID {
        unsigned long  Data1;
        unsigned short Data2;
        unsigned short Data3;
        unsigned char  Data4[ 8 ];
    } GUID;

    #define EXTERN_C    extern

    #define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
            EXTERN_C const GUID name \
                    = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

    DEFINE_GUID(WinUSB_TestGuid, 0xda812bff, 0x12c3, 0x46a2, 0x8e, 0x2b, 0xdb, 0xd3, 0xb7, 0x83, 0x4c, 0x43);
#endif

typedef const char *LPCSTR;

#define CERT_RETRIEVE_BIOMETRIC_PREDEFINED_BASE_TYPE    ((LPCSTR) 1000)
#define CERT_BIOMETRIC_SIGNATURE_TYPE           1
#define CERT_RETRIEVE_BIOMETRIC_SIGNATURE_TYPE          \
    (CERT_RETRIEVE_BIOMETRIC_PREDEFINED_BASE_TYPE + CERT_BIOMETRIC_SIGNATURE_TYPE)
