#include <Engine.h>
#include <chrono>
#include <iomanip>
#include "Resources.h"

using namespace Engine;

void Move(Camera& camera);
Vector3f& SetHill(Vector3f& vec);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();

	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(1280, 720, L"TestGame 3");

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)win->GetWidth() / (float)win->GetHeight(), 0.1f, 10000.0f);

	RenderTarget2D* target2D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer2D* renderer2D = renderSystem->CreateRenderer2D(target2D);
	Renderer3D* renderer3D = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight());

	LARGE_INTEGER time1;
	LARGE_INTEGER time2;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	Camera camera;

	Color4f clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Engine::Font* font;
	ExternFileManager::ReadFontFile("font.ttf", 50, Vector2f(0.001f, 0.001f), renderSystem->CreateTexture(), &font);

	Resources res(renderSystem);

	//Entities
	Entity entityLeaves(Vector3f(20.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(.1f, .1f, .1f), res.treeLeavesModel);
	Entity boba(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(180.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), res.bobaMesh);
	Entity island(Vector3f(-35.0f, -0.1f, -15.0f), Vector3f(0.0f, 100.0f, 0.0f), Vector3f(.1f, .1f, .1f), res.islandModel);

	//Terrain
	std::vector<uint> indices;
	Vertices vertices(200 * 200 * 4, Vertices::POSITION | Vertices::TEXCOORD | Vertices::NORMAL);
	{
		float size = 1.0f;
		float y = 0.0f;
		int c = 0;
		for (float x = -100.0f; x < 100.0f; x += 1.0f) {
			for (float z = -100.0f; z < 100.0f; z += 1.0f, c += 4) {
				vertices.GetPosition(c + 0) = SetHill(Vector3f(x, 0.0f, z));
				vertices.GetTexCoord(c + 0) = Vector2f(0.0f, 0.0f);
				vertices.GetNormal(c + 0) = Vector3f(0.0f, 1.0f, 0.0f);
				vertices.GetPosition(c + 1) = SetHill(Vector3f(x, y, z + size));
				vertices.GetTexCoord(c + 1) = Vector2f(0.0f, 1.0f);
				vertices.GetNormal(c + 1) = Vector3f(0.0f, 1.0f, 0.0f);
				vertices.GetPosition(c + 2) = SetHill(Vector3f(x + size, y, z + size));
				vertices.GetTexCoord(c + 2) = Vector2f(1.0f, 1.0f);
				vertices.GetNormal(c + 2) = Vector3f(0.0f, 1.0f, 0.0f);
				vertices.GetPosition(c + 3) = SetHill(Vector3f(x + size, y, z));
				vertices.GetTexCoord(c + 3) = Vector2f(1.0f, 0.0f);
				vertices.GetNormal(c + 3) = Vector3f(0.0f, 1.0f, 0.0f);
				indices.push_back(c + 0);
				indices.push_back(c + 1);
				indices.push_back(c + 2);
				indices.push_back(c + 2);
				indices.push_back(c + 3);
				indices.push_back(c + 0);
			}
		}
	}

	Texture* terrainTexture = renderSystem->CreateTexture();
	ExternFileManager::ReadTextureFile("grass.jpg", terrainTexture, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
	Material terrainMaterial = { 0xffffffff, terrainTexture };
	RawArray<const Material*> materials(1);
	materials[0] = &terrainMaterial;

	Model* terrainModel = new Model(renderSystem->CreateMesh(nullptr, false, Array<Mesh::Part>({ { indices.size(), (void*)&(indices[0]), vertices, sizeof(uint), false } })), materials);

	Entity terrain(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), terrainModel);

	//2D
	Text text0{ "", font, 0xff000000 };
	Text text1{ "", font, 0xff000000 };
	Quad textBack(Vector3f(-1.0f, 0.3f, 0.0f), Vector2f(0.4f, 0.3f), 0xfffff00f, res.emptyTex);
	Quad barkQuad(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.25, 0.25), 0xffffffff, res.leavesTexture);

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			QueryPerformanceCounter(&time1);

			renderSystem->BeginRendering(clearColor);

			renderer3D->Submit(&entityLeaves);
			renderer3D->Submit(&boba);
			renderer3D->Submit(&terrain);
			renderer3D->Submit(&island);
			renderer3D->Flush(camera.GetViewMatrix(), camera.GetPosition());

			renderer2D->Begin();
			renderer2D->Submit(&textBack);
			renderer2D->Submit(&barkQuad);
			renderer2D->DrawString(text0, Vector3f(-0.975f, 0.5f, 0.0f));
			renderer2D->DrawString(text1, Vector3f(-0.975f, 0.4f, 0.0f));
			renderer2D->End();
			renderer2D->Flush();

			renderSystem->EndRendering();

			((AnimatedModel*)boba.GetModel())->AddToAnimationTime(1.0f / 60.0f);
			if (((AnimatedModel*)boba.GetModel())->GetAnimationTime() >= ((AnimatedModel*)boba.GetModel())->GetAnimation()->GetDuration())
				((AnimatedModel*)boba.GetModel())->SetAnimationTime(0.0);

			Move(camera);

			QueryPerformanceCounter(&time2);
			LONGLONG time = (1000LL * (time2.QuadPart - time1.QuadPart)) / frequency.QuadPart;
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << 1000.0f / (float)time;
			text0.txt = "FPS: " + stream.str();
			text1.txt = "T: " + std::to_string(time) + "ms";
		}
	};

	renderSystem->Shutdown();
}

void Move(Camera& camera) {
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_LEFT)) {
		camera.GetRotation().y += 1.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_RIGHT)) {
		camera.GetRotation().y -= 1.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_UP)) {
		camera.GetRotation().x += 1.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_DOWN)) {
		camera.GetRotation().x -= 1.0f;
	}



	Vector3f look = Math::GetLookingDirection2D(camera.GetRotation());
	Vector3f orthLook = Matrix4f::Rotate(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;

	bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_W);
	bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_S);
	bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_A);
	bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_D);

	float speedFW = 0.1f;
	float speedSW = 0.1f;
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_STRG)) {
		speedFW = speedSW = 0.01f;
	}

	if (forward && !backward) {
		camera.GetPosition() += speedFW * look;
	} else if (!forward && backward) {
		camera.GetPosition() += -speedFW * look;
	}
	if (left && !right) {
		camera.GetPosition() += speedSW * orthLook;
	} else if (!left && right) {
		camera.GetPosition() += -speedSW * orthLook;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_SPACE)) {
		camera.GetPosition().y += 0.1f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(0x10)) {
		camera.GetPosition().y -= 0.1f;
	}

}

Vector3f& SetHill(Vector3f& vec) {
	if (vec.x > 50.0f && vec.x < 75.0f && vec.z > 30.0f && vec.z < 55.0f) {
		float a = 15.0f;
		float b = 2.0f * PI / 50.0f;
		vec.y = a * sin(vec.x * b + (-50.0f * b)) * sin(vec.z * b + (-30.0f * b));
	}
	return vec;
}
