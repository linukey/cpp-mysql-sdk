#ifndef __CPP_MYSQL_DB_DEFS_H__
#define __CPP_MYSQL_DB_DEFS_H__

#define DB_CHECK(exp, ...) { \
    if (exp) { \
        __VA_ARGS__; \
        return; \
    } \
}

#define DB_CHECK_RETURN(exp, ret, ...) { \
    if (exp) { \
        __VA_ARGS__; \
        return ret; \
    } \
}

#endif
