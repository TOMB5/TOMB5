#include "HWINSERT.H"
#include "GLOBAL.H"

TEXTUREBUCKET Bucket[MAXBUCKETS];

void InitBuckets()// (F)
{
	for (int n = 0; n < MAXBUCKETS; n++)
	{
		Bucket[n].tpage = 0xffffffff;
		Bucket[n].cnt = 0;
	}
}

D3DVALUE specular_thing[2080];

void SaveSpecular(TEXTUREBUCKET* buk)
{
	for(int i = 0; i < buk->cnt; i++)
	{
		if (buk->Vertex[i].specular & 0xFFFFFF)
		{
			specular_thing[i] = buk->Vertex[i].specular;
			buk->Vertex[i].specular = 0;
		}
		else
		{
			specular_thing[i] = 0;
		}
	}
}

void RestoreSpecular(TEXTUREBUCKET* buk)
{
	for (int i = 0; i < buk->cnt; i++)
	{
		if (specular_thing[i])
		{
			buk->Vertex[i].specular = specular_thing[i];
		}
	}
}
void DrawBuckets()
{
	if (App.tBumpMap)
	{
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	}

	Unimpl();
}