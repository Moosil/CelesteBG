//
// Created by School on 2025/3/12.
//

#include <game_window.h>

Game::Window::Window(int minFps): minFps(minFps), screenRect(Rect2<int>()) {
	assert(glfwInit());

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	const GLFWvidmode* mode = glfwGetVideoMode(nullptr);
 
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
 
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", nullptr, nullptr);
	
//	WNDCLASS wc = {sizeof(WNDCLASS)};
	const std::string className = "Celeste Pet Background";
	const std::string windowName = "Madline";
	
//	if (!GetClassInfo(GetModuleHandle(nullptr), className.c_str(), &wc)) {
//		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
//		wc.hInstance = GetModuleHandle(nullptr);
//		wc.lpszClassName = className.c_str();
//		wc.style = CS_HREDRAW | CS_VREDRAW;
//		wc.lpfnWndProc = &staticWindowProc;
//
//		assert(RegisterClass(&wc));
//	}

//	DEVMODEA devMode = {};
//	devMode.dmSize = sizeof(DEVMODEA);
//
//	EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &devMode);
	
//	m_hwnd = CreateWindowEx(
//	        WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_LAYERED,
//	        wc.lpszClassName,
//	        "Madline",
//	        WS_POPUP | WS_VISIBLE,
//	        0,
//	        0,
//	        static_cast<int>(devMode.dmPelsWidth),
//	        static_cast<int>(devMode.dmPelsHeight),
//	        nullptr, nullptr, GetModuleHandle(nullptr), this
//	);
	
//	assert(m_hwnd);
	
	m_window = glfwCreateWindow(
	        mode->width,
	        mode->height,
	        windowName.c_str(),
	        nullptr, nullptr
    );
	
	assert(m_window);
}

int Game::Window::mainLoop() {
	auto lastFrameTime = std::chrono::high_resolution_clock::now();
	
	while (!glfwWindowShouldClose(m_window)) {
		glfwPollEvents();
		
		if (!is_focused()) {
			resetInput(input);
		}
		
//		POINT point;
//		GetCursorPos(&point);
//		ScreenToClient(getHwnd(), &point);
//		input.cursorPos = Game::vec2iFromPoint(point);
//
//		RECT rect = {};
//		GetWindowRect(getHwnd(), &rect);
//		screenRect = rect;

		float dt = getDeltaTime(lastFrameTime);
		float adt = (dt > 1.f / (float) minFps) ? 1.f / (float) minFps : dt;// augmented delta time

		if (!Game::process(adt)) {
			running = false;
		}
		
		processInputAfter(input);
	}
	return 0;
}

void Game::Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//	Window* self;
//
//	if (msg == WM_NCCREATE)	{
//		auto *cs = (CREATESTRUCT*) lp;
//		self = static_cast<Window*>(cs->lpCreateParams);
//		self->m_hwnd = p_hwnd;
//		SetLastError(0);
//		if (SetWindowLongPtr(p_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self)) == 0)
//		{
//			if (GetLastError() != 0)
//				return false;
//		}
//	}
//	else
//	{
//		self = reinterpret_cast<Window*>(GetWindowLongPtr(p_hwnd, GWLP_USERDATA));
//	}
//
//	if (self)
//		return self->windowProc(msg, wp, lp);
//
//	return DefWindowProc(p_hwnd, msg, wp, lp);
}

//LRESULT Game::Window::windowProc(unsigned int msg, WPARAM wp, LPARAM lp) {
//	//	LRESULT rez = 0;
//	//
//	//	bool pressed = false;
//	//
//	//	switch (msg) {
//	//
//	//		case WM_CLOSE: {
//	//			running = false;
//	//			break;
//	//		}
//	//
//	//		case WM_LBUTTONDOWN: {
//	//			processEventButton(input.lmb, true);
//	//			break;
//	//		}
//	//
//	//		case WM_LBUTTONUP: {
//	//			processEventButton(input.lmb, false);
//	//			break;
//	//		}
//	//
//	//		case WM_RBUTTONDOWN: {
//	//			processEventButton(input.rmb, true);
//	//			break;
//	//		}
//	//
//	//		case WM_RBUTTONUP: {
//	//			processEventButton(input.rmb, false);
//	//			break;
//	//		}
//	//
//	//		case WM_SYSKEYDOWN: case WM_KEYDOWN:
//	//			pressed = true;
//	//		case WM_SYSKEYUP: case WM_KEYUP: {
//	//			bool altPressed = lp & (1 << 29);
//	//
//	//			for (int i = 0; i < Button::BUTTONS_COUNT; i++) {
//	//				if (wp == Button::buttonValues[i]) {
//	//					processEventButton(input.keyBoard[i], pressed);
//	//					input.keyBoard[i].altPressed = altPressed;
//	//				}
//	//			}
//	//
//	//			// so alt + f4 works
//	//			rez = DefWindowProc(m_hwnd, msg, wp, lp);
//	//		} break;
//	//
//	//		case WM_SETFOCUS: {
//	//			set_focused(true);
//	//			break;
//	//		}
//	//
//	//		case WM_KILLFOCUS: {
//	//			set_focused(false);
//	//			break;
//	//		}
//	//
//	//		case WM_WINDOWPOSCHANGING: {
//	//			auto *pos = (WINDOWPOS *) lp;
//	//
//	//			if (pos->x == -32000) {
//	//				// Set the flags to prevent this and "survive" to the desktop toggle
//	//				pos->flags |= SWP_NOMOVE | SWP_NOSIZE;
//	//			}
//	//
//	//			pos->hwndInsertAfter = HWND_BOTTOM;
//	//			break;
//	//		}
//	//
//	//		case WM_NCHITTEST: {
//	//			rez = HTNOWHERE;
//	//			break;
//	//		}
//	//
//	//        default: {
//	//			rez = DefWindowProc(m_hwnd, msg, wp, lp);
//	//			break;
//	//		}
//	//	}
//	//	return rez;
//}

float Game::Window::getDeltaTime(std::chrono::high_resolution_clock::time_point &lastFrameTime) {
	auto now = std::chrono::high_resolution_clock::now();
	
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrameTime).count();
	float rez = (float) microseconds / 1000000.0f;
	lastFrameTime = std::chrono::high_resolution_clock::now();
	return rez;
}

#pragma region input
void Game::Window::set_focused(bool val) {
	input.focused = val;
}

bool Game::Window::is_focused() const {
	return input.focused;
}

bool Game::Window::is_button_pressed(int buttonIndex) {
	return input.keyBoard[buttonIndex].pressed;
}

bool Game::Window::is_button_triggered(int buttonIndex) {
	return input.keyBoard[buttonIndex].triggered;
}

bool Game::Window::is_button_held(int buttonIndex) {
	return input.keyBoard[buttonIndex].held;
}

bool Game::Window::is_button_released(int buttonIndex) {
	return input.keyBoard[buttonIndex].released;
}

bool  Game::Window::is_lmb_pressed() const {
	return input.lmb.pressed;
}

bool  Game::Window::is_lmb_triggered() const {
	return input.lmb.pressed;
}

bool  Game::Window::is_lmb_held() const {
	return input.lmb.pressed;
}

bool  Game::Window::is_lmb_released() const {
	return input.lmb.pressed;
}

bool  Game::Window::is_rmb_pressed() const {
	return input.rmb.pressed;
}

bool  Game::Window::is_rmb_triggered() const {
	return input.rmb.pressed;
}

bool  Game::Window::is_rmb_held() const {
	return input.rmb.pressed;
}

bool  Game::Window::is_rmb_released() const {
	return input.rmb.pressed;
}

std::vector<int> Game::Window::get_buttons_pressed() {
	std::vector<int> pressed;
	for (int i = 0; i < Button::BUTTONS_COUNT; i++) {
		if (input.keyBoard[i].pressed) {
			pressed.push_back(i);
		}
	}
	return pressed;
}

std::vector<int> Game::Window::get_buttons_triggered() {
	std::vector<int> triggered;
	for (int i = 0; i < Button::BUTTONS_COUNT; i++) {
		if (input.keyBoard[i].triggered) {
			triggered.push_back(i);
		}
	}
	return triggered;
}

std::vector<int> Game::Window::get_buttons_held() {
	std::vector<int> held;
	for (int i = 0; i < Button::BUTTONS_COUNT; i++) {
		if (input.keyBoard[i].held) {
			held.push_back(i);
		}
	}
	return held;
}

std::vector<int> Game::Window::get_buttons_released() {
	std::vector<int> released;
	for (int i = 0; i < Button::BUTTONS_COUNT; i++) {
		if (input.keyBoard[i].released) {
			released.push_back(i);
		}
	}
	return released;
}
#pragma endregion
