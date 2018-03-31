#pragma once

#include "IGraphics.h"
#include "Consts.h"
#include "SpriteRendererComponent.h" 
#include "TextRendererComponent.h"
#include "Animation.h"
//#include "TextureManager.h"

#include <cassert>
#include <map>
#include <memory>

#include <d3d11.h>
#include "DirectXTK\Inc\SpriteBatch.h"
#include "DirectXTK\Inc\SpriteFont.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"
#include "directxtk\Inc\PrimitiveBatch.h"
#include "directxtk\Inc\VertexTypes.h"

using namespace DirectX;
class TextureManager;
class DxGraphics : public IGraphics
{
public:
	DxGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher);


	virtual void Initalise(class HWNDKey& key) override;
	virtual void Destroy() override;

	virtual void EndFrame() override;
	virtual void BeginFrame() override;

	virtual void DrawComponent(IDrawableComponent* component);

	void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset);

	//void DrawText(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset);

	void DrawText(std::string text, Vec2 pos, float rot, float4 * rgb3, float scale, Vec2 offset);

	void DrawLine(Vec2 v1, Vec2 v2);

	HRESULT LoadTexture(std::string path);
	ID3D11ShaderResourceView* GetTexture(std::string path);

	//friend ID3D11ShaderResourceView * TextureManager::GetTexture(DxGraphics &dxGraphics, std::string path);
	//friend HRESULT TextureManager::LoadTexture(DxGraphics &dxGraphics, std::string path);
	friend class TextureManager;
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x, y, z;		// position
		float u, v;			// texcoords
	};

	Microsoft::WRL::ComPtr<IDXGISwapChain>					_swapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>					_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>				_immediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>					_sysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		_sysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>				_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>				_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>					_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>				_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>				_samplerState;

	std::unique_ptr<SpriteBatch>							_sprites;
	std::unique_ptr<SpriteFont>								_fonts;
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>>	_primitiveBatch;
	/*static*/ std::map<std::string, ID3D11ShaderResourceView*>		_textures;
	TextureManager * _textureManager;
	std::map<std::string, std::vector<Animation>>_animations; //TODO : load all animations according to the texture path
	Animation _animation;
};

class TextureManager
{
public:
	//static std::map<std::string, ID3D11ShaderResourceView*> _texturesMap;
	//static std::map<std::string name, std::string path> _namePath;
	static TextureManager* GetInstance();

	//HRESULT RetrieveTexture(std::map<std::string, ID3D11ShaderResourceView*> textures, std::string name, ID3D11ShaderResourceView* textureOut);
	ID3D11ShaderResourceView * GetTexture(DxGraphics &dxGraphics, std::string path);
	HRESULT LoadTexture(DxGraphics &dxGraphics, std::string path);

private:
	TextureManager();
	~TextureManager();
	static TextureManager* _instance;
};

