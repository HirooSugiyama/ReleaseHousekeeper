
#pragma once


class DirectX11 final
{
private:
    // 静的なGraphics のポインタを宣言する
    static std::unique_ptr <DirectX11> sDirectX11;

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;


    DirectX11();
public:
    ~DirectX11() = default;
    void CreateDevice();
    void CreateResources();
    void OnDeviceLost();


    // ウィンドウハンドルを設定する
    void SetHWND(const HWND& hWnd);
    // デフォルトサイズを設定する
    void SetDefaultSize(const int& width, const int& height);
    //ウィンドウサイズを取得する
    int GetOutputWidth();
    int GetOutputHeight();

    // デバイスを取得する
    Microsoft::WRL::ComPtr <ID3D11Device1> GetDevice() const;
    // コンテキストを取得する
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> GetContext() const;
    // スワップチェーンを取得する
    Microsoft::WRL::ComPtr<IDXGISwapChain1> GetSwapChain() const;
    // レンダーターゲットビューを取得する
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const;
    // デプスステンシルビューを取得する
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const;

    // Graphics オブジェクトへのポインタを返す
    static DirectX11& GetRefInstance()
    {
        // s_graphics がnull の場合
        if (sDirectX11 == nullptr)
        {
            // Graphics オブジェクトを生成し、そのポインタをs_graphics に格納する
            sDirectX11.reset(new DirectX11);
        }
        return *sDirectX11.get();
    }
};


