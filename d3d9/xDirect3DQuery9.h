#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DQuery9 : public IDirect3DQuery9
{
public:
	xDirect3DQuery9( IDirect3DQuery9* query );
	~xDirect3DQuery9() {}

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP_(D3DQUERYTYPE) GetType( THIS );

	virtual STDMETHODIMP_(DWORD) GetDataSize( THIS );

	virtual STDMETHODIMP Issue( THIS_ DWORD dwIssueFlags );

	virtual STDMETHODIMP GetData( THIS_ void* pData,DWORD dwSize,DWORD dwGetDataFlags );

	IDirect3DQuery9* m_query;
};