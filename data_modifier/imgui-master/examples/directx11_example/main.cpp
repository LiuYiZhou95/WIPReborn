// ImGui - standalone example application for DirectX 11
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <imgui.h>

#include "imgui_impl_dx11.h"
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <string>
#include "RBMath/Inc/RBMath.h"
#include "RBMath/Inc/Vector2.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "imgui_dock.h"

// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

void CreateRenderTarget()
{
    DXGI_SWAP_CHAIN_DESC sd;
    g_pSwapChain->GetDesc(&sd);

    // Create the render target
    ID3D11Texture2D* pBackBuffer;
    D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
    ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
    render_target_view_desc.Format = sd.BufferDesc.Format;
    render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

HRESULT CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    }

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return E_FAIL;

    CreateRenderTarget();

    return S_OK;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            ImGui_ImplDX11_InvalidateDeviceObjects();
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
            ImGui_ImplDX11_CreateDeviceObjects();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int main(int, char**)
{
    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, _T("ImGui Example"), NULL };
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindow(_T("ImGui Example"), _T("ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (CreateDeviceD3D(hwnd) < 0)
    {
        CleanupDeviceD3D();
        UnregisterClass(_T("ImGui Example"), wc.hInstance);
        return 1;
    }

    // Show the window
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Setup ImGui binding
    ImGui_ImplDX11_Init(hwnd, g_pd3dDevice, g_pd3dDeviceContext);

    // Setup style
    ImGui::StyleColorsClassic();
    //ImGui::StyleColorsDark();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'extra_fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui::LoadDock();

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        ImGui_ImplDX11_NewFrame();

        // 1. Show a simple window.
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
            if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
                show_demo_window ^= 1;
            if (ImGui::Button("Another Window"))
                show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			if (ImGui::Begin("Dock Demo"))
			{
				// dock layout by hard-coded or .ini file
				ImGui::BeginDockspace();

				if (ImGui::BeginDock("Dock 1")) {
					ImGui::Text("Hi");
				}
				ImGui::EndDock();

				if (ImGui::BeginDock("Dock 2")) {
					ImGui::Text("I'm BentleyBlanks!");
				}
				ImGui::EndDock();

				if (ImGui::BeginDock("Dock 3")) {
					ImGui::Text("Hello World");
				}
				ImGui::EndDock();

				ImGui::EndDockspace();
			}
			ImGui::End();

			do
			{
				if (ImGui::Button("Open..", ImVec2(100, 50)))
				{
					std::wstring name;
					OPENFILENAME ofn = { 0 };
					TCHAR strFilename[MAX_PATH] = { 0 };
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = NULL;
					ofn.lpstrFilter = TEXT("Scene Flie\0*.data\0\0");
					ofn.nFilterIndex = 1;
					ofn.lpstrFile = strFilename;
					ofn.nMaxFile = sizeof(strFilename);
					ofn.lpstrInitialDir = NULL;
					ofn.lpstrTitle = TEXT("请选择一个数据集");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
					if (GetOpenFileName(&ofn))
					{
						name = strFilename;
						struct data_pak_t
						{
							RBVector2 player_pos;
							RBVector2 enemey_pos;
							RBVector2 player_bullet_pos;
							RBVector2 enemey_bullet_pos;
							int is_shotting;
							int is_dying;
							f32 cur_time_ms;
						};

						std::vector<data_pak_t> vout;

						std::ifstream fin(name.data(), std::ios::binary);
						fin.seekg(0, fin.end);
						int read_size = fin.tellg();
						fin.seekg(0, fin.beg);
						int n = read_size / sizeof(data_pak_t);
						data_pak_t* ds = new data_pak_t[n];
						fin.read((char*)ds, read_size);
						fin.close();

						int k = 0;
						int j = 0;
						int ki = 0;
						for (int i = 0; i < n; i++)
						{
							/*
							ds[i].player_pos.out();
							ds[i].enemey_pos.out();
							ds[i].player_bullet_pos.out();
							ds[i].enemey_bullet_pos.out();
							std::cout << "shoting:" << ds[i].is_shotting << std::endl;
							std::cout << "dying:" << ds[i].is_dying << std::endl;
							std::cout << "time:" << ds[i].cur_time_ms << std::endl;
							*/
							if (ds[i].is_dying)
							{
								k++;
								
								f32 time = ds[i].cur_time_ms;
								for (int jj = ki; jj < i; ++jj)
								{
									ds[jj].cur_time_ms = RBMath::abs( time - ds[jj].cur_time_ms);
									vout.push_back(ds[jj]);
								}
								ds[i].cur_time_ms = 0.f;
								vout.push_back(ds[i]);
								ki = i+1;
							}
							j++;
						}

						std::cout << "======\n" << "total training number:" << k << std::endl;
						std::cout << "======\n" << "total data number:" << j << std::endl;


						std::ofstream fout("d:/dt.data",  std::ios::app);
						for (int i = 0; i < vout.size(); ++i)
						{
							int a = (int)(vout[i].cur_time_ms / 1000.f);
							if (a > 9)
								a = 9;
							
							int r = RBMath::get_rand_range_i(0, 8);
							if(r<=2||r>=5)
								continue;
								
							fout<<vout[i].player_pos.x<<','<<
								vout[i].player_pos.y<<','<<
								vout[i].enemey_pos.x<<','<<
								vout[i].enemey_pos.y<<','<<
								//we made a mistake ! current enemey bullet is player bullet!
							vout[i].enemey_bullet_pos.x<<','<<
							vout[i].enemey_bullet_pos.y<<','
							 <<a<<std::endl;
						}
						fout.close();
					}
					else
					{
						break;
					}
				}
			} while (false);


        }

        // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            ImGui::End();
        }

        // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
        if (show_demo_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // Rendering
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
        ImGui::Render();

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }
	ImGui::SaveDock();
    ImGui_ImplDX11_Shutdown();
    CleanupDeviceD3D();
    UnregisterClass(_T("ImGui Example"), wc.hInstance);

    return 0;
}
