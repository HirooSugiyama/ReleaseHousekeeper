
#pragma once


class DirectX11 final
{
private:
    // �ÓI��Graphics �̃|�C���^��錾����
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


    // �E�B���h�E�n���h����ݒ肷��
    void SetHWND(const HWND& hWnd);
    // �f�t�H���g�T�C�Y��ݒ肷��
    void SetDefaultSize(const int& width, const int& height);
    //�E�B���h�E�T�C�Y���擾����
    int GetOutputWidth();
    int GetOutputHeight();

    // �f�o�C�X���擾����
    Microsoft::WRL::ComPtr <ID3D11Device1> GetDevice() const;
    // �R���e�L�X�g���擾����
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> GetContext() const;
    // �X���b�v�`�F�[�����擾����
    Microsoft::WRL::ComPtr<IDXGISwapChain1> GetSwapChain() const;
    // �����_�[�^�[�Q�b�g�r���[���擾����
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const;
    // �f�v�X�X�e���V���r���[���擾����
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const;

    // Graphics �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
    static DirectX11& GetRefInstance()
    {
        // s_graphics ��null �̏ꍇ
        if (sDirectX11 == nullptr)
        {
            // Graphics �I�u�W�F�N�g�𐶐����A���̃|�C���^��s_graphics �Ɋi�[����
            sDirectX11.reset(new DirectX11);
        }
        return *sDirectX11.get();
    }
};


