#ifndef __RBUFFER_H__
#define __RBUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RB_NPOS(rb,pos)  (((rb)->pos+1 >= (rb)->qsize) ? (0) : ((rb)->pos+1))
#define RB_EMPTY(rb)     ((rb)->wpos == (rb)->rpos)
#define RB_FULL(rb)      (RB_NPOS(rb, wpos) == (rb)->rpos)
#define RB_COUNT(rb)     (((rb)->rpos <= (rb)->wpos)?\
                          ((rb)->wpos - (rb)->rpos):\
                          ((rb)->qsize-(rb)->rpos + (rb)->wpos))

/*ringbuffer define*/
#define RBUFFER_DEF(name, type, size) \
    struct rb_#name {\
        int  rpos, wpos, qsize;\
        type rbq[(size)+1];\
    }name;

/*ringbuffer define (refference)*/
#define RBUFFER_DEF_R(name, type, size) \
    struct rb_#name{\
        int  rpos, wpos, qsize;\
        type *rbq;\
    }name;

/*ringbuffer define (internal)*/
#define RBUFFER_IDEF(name, type, size) \
    struct {\
        int  rpos, wpos, qsize;\
        type rbq[(size)+1];\
    }name

/*ringbuffer define (internal & refference)*/
#define RBUFFER_IDEF_R(name, type, size) \
    struct {\
        int  rpos, wpos, qsize;\
        type *rbq;\
    }name

/*get a value from ringbuffer*/
#define RB_GET(rb, val) do{\
        if(!RB_EMPTY(rb)){\
            val = (rb)->rbq[(rb)->rpos];\
            (rb)->rpos = RB_NPOS((rb), rpos);\
        }\
    } while(0)

/*set a value into ringbuffer*/
#define RB_SET(rb, val) do{\
        if(!RB_FULL(rb)){\
            (rb)->rbq[(rb)->wpos] = val;\
            (rb)->wpos = RB_NPOS((rb), wpos);\
        }\
    } while (0)

/*set a value into ringbuffer, allow override old data*/
#define RB_SET_OR(rb, val) do{\
        if(RB_FULL(rb)){\
            (rb)->rpos = RB_NPOS((rb), rpos);\
        }\
        (rb)->rbq[(rb)->wpos] = val;\
        (rb)->wpos = RB_NPOS((rb), wpos);\
    } while (0)

/*ringbuffer init*/
#define RB_INIT(rb, size) do{\
        (rb)->qsize = (size);\
        (rb)->rpos = 0;\
        (rb)->wpos = 0;\
    } while (0)

/*ringbuffer init (referrence mode)*/
#define RB_INIT_R(rb, size, buff) do{\
        (rb)->qsize = (size);\
        (rb)->rpos = 0;\
        (rb)->wpos = 0;\
        (rb)->rbq  = buff;\
    } while (0)

#ifdef __cplusplus
}
#endif


#endif
