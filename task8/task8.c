#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LIST_BY_YEAR       0
#define LIST_BY_TYPE       1

#define TYPE_MAX           100
#define SETUP_MAX          100

typedef struct TEngine
{
  struct TEngine * m_Next;
  int              m_Year;
  char             m_Type  [ TYPE_MAX ];
  int              m_Setup [ SETUP_MAX ];
} TENGINE;

typedef struct TArchive
{
  struct TArchive * m_Next;
  TENGINE         * m_Engines;
} TARCHIVE;

TENGINE          * createEngine                            ( const char      * type,
                                                             int               year )
{
  TENGINE * res = (TENGINE *) malloc ( sizeof  (*res ) );
  res -> m_Next = NULL;
  res -> m_Year = year;
  strncpy ( res -> m_Type, type, sizeof ( res -> m_Type ) );
  for ( int i = 0; i < SETUP_MAX; i ++ )
    res -> m_Setup[i] = 0;
  return res;
}
#endif /* __PROGTEST__ */
//Credits go to my friends and some random people from India. Shit does not work tho. Pls dont kick me out ay laamao. Happy holiday

TARCHIVE * AddEngine(TARCHIVE * list, int listBy, TENGINE * engine) {
        int strcmpRes = 0;
        TENGINE * currentEngine = NULL, * tempcurrentEngine = NULL;
        TARCHIVE * archpoint = NULL;
        if (list == NULL) {
                TARCHIVE * list = (TARCHIVE * ) malloc(sizeof( * list));
                if (list == NULL) return NULL;
                list -> m_Next = NULL;
                list -> m_Engines = engine;
                return list;
        }
        switch (listBy) {
        case LIST_BY_YEAR:
                for (archpoint = list; /*void*/ ; archpoint = archpoint -> m_Next) {
                        if (archpoint -> m_Engines -> m_Year == engine -> m_Year) {
                                tempcurrentEngine = archpoint -> m_Engines;
                                for (currentEngine = archpoint -> m_Engines; /*void*/ ; currentEngine = currentEngine -> m_Next) {
                                        strcmpRes = strcmp(currentEngine -> m_Type, engine -> m_Type);
                                        if (strcmpRes == 0) {
                                                engine -> m_Next = currentEngine -> m_Next;
                                                currentEngine -> m_Next = engine;
                                                return list;
                                        }

                                        if (strcmpRes > 0) {
                                                if ((currentEngine -> m_Next == NULL && archpoint -> m_Engines -> m_Next == NULL) || tempcurrentEngine == currentEngine) {
                                                        engine -> m_Next = currentEngine;
                                                        currentEngine = engine;
                                                        archpoint -> m_Engines = currentEngine;
                                                        return list;
                                                } else {
                                                        engine -> m_Next = currentEngine;
                                                        currentEngine = engine;
                                                        tempcurrentEngine -> m_Next = currentEngine;
                                                        return list;
                                                }

                                        }
                                        if (currentEngine -> m_Next == NULL) {
                                                engine -> m_Next = currentEngine -> m_Next;
                                                currentEngine -> m_Next = engine;
                                                return list;
                                        }
                                        tempcurrentEngine = currentEngine;
                                }
                        }

                        if (archpoint -> m_Engines -> m_Year > engine -> m_Year) {
                                TARCHIVE * tmpArchpoint = (TARCHIVE * ) malloc(sizeof( * list));

                                tmpArchpoint -> m_Next = archpoint -> m_Next;
                                archpoint -> m_Next = tmpArchpoint;

                                archpoint -> m_Next -> m_Engines = archpoint -> m_Engines;
                                archpoint -> m_Engines = engine;

                                return list;

                        }
                        if (archpoint -> m_Next == NULL) {
                                TARCHIVE * tmpArchpoint = (TARCHIVE * ) malloc(sizeof( * list));

                                archpoint -> m_Next = tmpArchpoint;

                                archpoint -> m_Next -> m_Engines = engine;

                                return list;
                        }

                }
                break;
        case LIST_BY_TYPE:
                for (archpoint = list; /*void*/ ; archpoint = archpoint -> m_Next) {
                        strcmpRes = strcmp(archpoint -> m_Engines -> m_Type, engine -> m_Type);
                        if (strcmpRes == 0) {
                                for (currentEngine = archpoint -> m_Engines; /*void*/ ; currentEngine = currentEngine -> m_Next) {
                                        if (currentEngine -> m_Year == engine -> m_Year) {
                                                engine -> m_Next = currentEngine -> m_Next;
                                                currentEngine -> m_Next = engine;
                                                return list;
                                        }
                                        if (currentEngine -> m_Year > engine -> m_Year) {

                                                engine -> m_Next = currentEngine;
                                                currentEngine = engine;
                                                archpoint -> m_Engines = currentEngine;
                                                return list;

                                        }
                                        if (currentEngine -> m_Next == NULL) {
                                                engine -> m_Next = currentEngine -> m_Next;
                                                currentEngine -> m_Next = engine;
                                                return list;
                                        }

                                }
                        }

                        if (strcmpRes > 0) {
                                TARCHIVE * tmpArchpoint = (TARCHIVE * ) malloc(sizeof( * list));
                                tmpArchpoint -> m_Next = archpoint -> m_Next;
                                archpoint -> m_Next = tmpArchpoint;
                                archpoint -> m_Next -> m_Engines = archpoint -> m_Engines;
                                archpoint -> m_Engines = engine;

                                return list;

                        }
                        if (archpoint -> m_Next == NULL) {
                                TARCHIVE * tmpArchpoint = (TARCHIVE * ) malloc(sizeof( * list));
                                tmpArchpoint -> m_Next = NULL;
                                archpoint -> m_Next = tmpArchpoint;

                                archpoint -> m_Next -> m_Engines = engine;
                                return list;

                        }
                }

                break;

        default:
                return NULL;
                break;
        }

}
void DelArchive(TARCHIVE * list) {
        TENGINE * currentEngine, * prevEngine;
        TARCHIVE * archpointer, * prevArchpointer;
        if (list == NULL) return;
        archpointer = list -> m_Next;
        currentEngine = list -> m_Engines;
        while (currentEngine) {
                prevEngine = currentEngine;
                currentEngine = currentEngine -> m_Next;
                free(prevEngine);
        }

        while (archpointer) {
                currentEngine = archpointer -> m_Engines;
                while (currentEngine) {
                        prevEngine = currentEngine;
                        currentEngine = currentEngine -> m_Next;
                        free(prevEngine);
                }
                archpointer = archpointer -> m_Next;
        }
        archpointer = list -> m_Next;
        while (archpointer) {
                prevArchpointer = archpointer;
                archpointer = archpointer -> m_Next;
                free(prevArchpointer);
        }
        free(list);

}
TARCHIVE * ReorderArchive(TARCHIVE * list, int listBy) {
        TARCHIVE * newlist = NULL, * tmparchpointer = NULL;
        TENGINE * currentEngine = NULL, * tmpEngine = NULL;
        if (list == NULL) return list;
        switch (listBy) {
        case LIST_BY_YEAR:
                tmparchpointer = list;
                while (tmparchpointer != NULL)

                {
                        currentEngine = tmparchpointer -> m_Engines;
                        tmparchpointer = tmparchpointer -> m_Next;
                        while (currentEngine != NULL)

                        {
                                tmpEngine = currentEngine;

                                currentEngine = currentEngine -> m_Next;
                                tmpEngine -> m_Next = NULL;
                                newlist = AddEngine(newlist, LIST_BY_YEAR, tmpEngine);

                        }

                }
                while (list != NULL) {
                        TARCHIVE * p = list -> m_Next;
                        free(list);
                        list = p;
                }

                return newlist;
                break;
        case LIST_BY_TYPE:
                tmparchpointer = list;
                while (tmparchpointer != NULL)

                {
                        currentEngine = tmparchpointer -> m_Engines;
                        tmparchpointer = tmparchpointer -> m_Next;
                        while (currentEngine != NULL)

                        {
                                tmpEngine = currentEngine;

                                currentEngine = currentEngine -> m_Next;
                                tmpEngine -> m_Next = NULL;
                                newlist = AddEngine(newlist, LIST_BY_TYPE, tmpEngine);

                        }

                }
                while (list != NULL) {
                        TARCHIVE * p = list -> m_Next;
                        free(list);
                        list = p;
                }
                return newlist;
                break;

        default:
                return NULL;
                break;
        }

}

#ifndef __PROGTEST__
int                main                                    ( int               argc,
                                                             char            * argv [] )
{
  TARCHIVE * a;

  a = NULL;
  return 0;
}
#endif /* __PROGTEST__ */