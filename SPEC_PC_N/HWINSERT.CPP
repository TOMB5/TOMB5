#include "HWINSERT.H"
#include "GLOBAL.H"
#include "PICTURE.H"

TEXTUREBUCKET Bucket[MAXBUCKETS];

void InitBuckets()// (F)
{
	for (int n = 0; n < MAXBUCKETS; n++)
	{
		Bucket[n].tpage = -1;
		Bucket[n].cnt = 0;
	}
}

D3DVALUE specular_thing[VERTSPERBUCKET];

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

void FindBucket(uint16_t tile, D3DTLBUMPVERTEX** vptr, int** cntptr)
{
	auto ptr = Bucket;
	for(int i = 0; i < MAXBUCKETS; i++, ptr++)
	{
		if (ptr->tpage == tile && ptr->cnt > 2048)
		{
			*vptr = &ptr->Vertex[ptr->cnt];
			*cntptr = &ptr->cnt;
			return;
		}

		if (ptr->cnt > 2048)
		{
			Log(LT_Info, "Bucket count over 2048, resetting");
			DrawBucket(ptr);

			ptr->tpage = tile;
			ptr->cnt = 0;

			*vptr = ptr->Vertex;
			*cntptr = &ptr->cnt;
			return;
		}
	}

	int max_cnt = 0, max_i = 0;
	ptr = Bucket;
	for (int i = 0; i < MAXBUCKETS; i++, ptr++)
	{
		if (ptr->tpage == -1)
		{
			ptr->tpage = tile;
			*vptr = ptr->Vertex;
			*cntptr = &ptr->cnt;
			return;
		}

		if (ptr->cnt > max_cnt)
		{
			max_cnt = ptr->cnt;
			max_i = i;
		}
	}

	DrawBucket(&Bucket[max_i]);
	Bucket[max_i].tpage = tile;
	Bucket[max_i].cnt = 0;
	*vptr = Bucket[max_i].Vertex;
	*cntptr = &Bucket[max_i].cnt;
}

void DrawBucket(TEXTUREBUCKET* buk)
{
	if (buk->tpage == 1) // here be dragons
		buk->tpage = 1;

	Log(LT_Info, "DrawBucket id=%2d; tpage=%d; cnt=%d", buk - Bucket, buk->tpage, buk->cnt);

	if (buk->cnt != 0)
	{
		if (DXTextureList[buk->tpage].alpha_blend && App.tBumpMap)
		{
			SaveSpecular(buk);

			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);

			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

			DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[DXTextureList[buk->tpage].other_id].tex));

			App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, buk->Vertex, buk->cnt, D3DDP_DONOTCLIP);

			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCCOLOR);

			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

			RestoreSpecular(buk);

			App.DrawPrimitiveCntBuk++;
		}

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[buk->tpage].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, buk->Vertex, buk->cnt, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
		buk->tpage = -1;
		buk->cnt = 0;

		if (App.tBumpMap)
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

		App.DrawPrimitiveCntBuk++;
	}
}

void DrawBuckets()
{
	if (App.tBumpMap)
	{
		Log(LT_Info, "DrawBuckets - bumpmap");

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		auto buk = Bucket;
		for(int i = 0; i < MAXBUCKETS; i++, buk++)
		{
			if (buk->cnt != 0 && DXTextureList[buk->tpage].alpha_blend)
			{
				SaveSpecular(buk);
				DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[DXTextureList[buk->tpage].other_id].tex));
				App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, buk->Vertex, buk->cnt, D3DDP_DONOTCLIP);
				RestoreSpecular(buk);
				App.DrawPrimitiveCntBuk++;
			}
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCCOLOR);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		buk = Bucket;
		for (int i = 0; i < MAXBUCKETS; i++, buk++)
		{
			if (buk->cnt != 0 && DXTextureList[buk->tpage].alpha_blend)
			{
				DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[buk->tpage].tex));
				App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, buk->Vertex, buk->cnt, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
				buk->tpage = -1;
				buk->cnt = 0;
				App.DrawPrimitiveCntBuk++;
			}
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

		buk = Bucket;
		for (int i = 0; i < MAXBUCKETS; i++, buk++)
		{
			if (buk->cnt != 0 && !DXTextureList[buk->tpage].alpha_blend)
			{
				DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[buk->tpage].tex));
				App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, buk->Vertex, buk->cnt, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
				buk->tpage = -1;
				buk->cnt = 0;
				App.DrawPrimitiveCntBuk++;
			}
		}
	}
	else
	{
		Log(LT_Info, "DrawBuckets - NO bumpmap");

		for (int i = 0; i < MAXBUCKETS; i++)
		{
			DrawBucket(&Bucket[i]);
		}
	}
}