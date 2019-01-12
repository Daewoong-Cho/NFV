#include	"shm_def.h"
#include	"common.h"


#define pFunc int(*)(const void*, const void*)

// 옵션 12자리 종목코드로 비교
static int cmp_stnd_iscd(const char* fcode, CODEIDX_OPT* codeidx)
{
    return (memcmp(fcode, codeidx->stnd_iscd, sizeof(codeidx->stnd_iscd)-1));
}

// 옵션 12자리 종목코드로 정렬
static int sort_stnd_iscd(const CODEIDX_OPT* code1, const CODEIDX_OPT* code2)
{
    return (strncmp(code1->stnd_iscd, code2->stnd_iscd, sizeof(code1->stnd_iscd)-1));
}

// 옵션 8자리 단축코드로 비교
static int cmp_shrn_iscd(const char* shrn_iscd, CODEIDX_OPT* codeidx)
{
    return (memcmp(shrn_iscd, codeidx->shrn_iscd, sizeof(codeidx->shrn_iscd)-1));
}

// 8자리 단축코드로 정렬
static int sort_shrn_iscd(const CODEIDX_OPT* code1, const CODEIDX_OPT* code2)
{
    return (strncmp(code1->shrn_iscd, code2->shrn_iscd, sizeof(code1->shrn_iscd)-1));
}

// codeindex에서 full code(12)로 지수옵션종목 위치를 찾음 
int OffsetOptf(char *fullcode)
{
    CODEIDX_OPT		*key;
    int             tcnt, size;

    tcnt = koshm->tot_lst_cnt;

    size = sizeof(CODEIDX_OPT);

    key = (CODEIDX_OPT *)bsearch((void*)fullcode, (void*)&koshm->fcodeidx[0],
            tcnt, size, (pFunc)cmp_stnd_iscd);
    if (key == NULL)
    {
        return (-1);
    }

    return (key->offs);
}

// codeindex에 지수옵션종목 위치를 추가하고 새로운 위치를 돌려줌.
int AddOpt(CODEIDX_OPT *incd)
{
    int             tcnt, size;

    tcnt = koshm->tot_lst_cnt;
    size = sizeof(CODEIDX_OPT);

    if(++tcnt > KO_LIST_COUNT)   /* 최대종목수를 초과하면 에러리턴 */
    {
        return (-1);
    }

    koshm->tot_lst_cnt = tcnt;

    koshm->fcodeidx[tcnt-1].offs = tcnt-1;
    memcpy(koshm->fcodeidx[tcnt-1].stnd_iscd, incd->stnd_iscd, sizeof(incd->stnd_iscd)-1);
    memcpy(koshm->fcodeidx[tcnt-1].shrn_iscd, incd->shrn_iscd, sizeof(incd->shrn_iscd)-1);

    qsort((void *)koshm->fcodeidx, tcnt, size, (pFunc)sort_stnd_iscd);

    koshm->scodeidx[tcnt-1].offs = tcnt-1;
    memcpy(koshm->scodeidx[tcnt-1].stnd_iscd, incd->stnd_iscd, sizeof(incd->stnd_iscd)-1);
    memcpy(koshm->scodeidx[tcnt-1].shrn_iscd, incd->shrn_iscd, sizeof(incd->shrn_iscd)-1);

    qsort((void *)koshm->scodeidx, tcnt, size, (pFunc)sort_shrn_iscd);

    return (tcnt-1);
}
