//=============================================================================
//
// ???C??
// Author:?????]??
//
//=============================================================================

//=============================================================================
// ?C???N???[?h
//=============================================================================
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#include <math.h>
#include <assert.h>
#include "xaudio2.h"	//?T?E???h?????ɕK?v
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG

//???i?g?p?֎~
#ifdef CHECK_MEM_LEAK
#define DEBUG new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

//#pragma push_macro("new")
//#undef new
//#include <d3dx9.h>
//#pragma pop_macro("new")

//=============================================================================
// ?}?N?????`
//=============================================================================
#define MAX_OBJECT		(512)		//?I?u?W?F?N?g?̍ő吔
#define MAX_PRIO		(5)			//?D?揇?ʂ̍ő吔

//=============================================================================
// ?O???錾
//=============================================================================
class CObject;

//=============================================================================
// ?v???g?^?C?v?錾
//=============================================================================
int GetFPS(void);