#pragma once

/// <summary>
/// Window‚Ì’è‹`‚ð‚µ‚Ü‚·
/// </summary>
namespace Screen
{
	static const int WIDTH = 1920;
	static const int HEIGHT = 1080;
	static const int WIDTHSMALL = 1600;
	static const int HEIGHTSMALL = 720;
	static const BOOL WINDOW_MODE = TRUE;
	static const char* WINDOW_NAME = "project";
	static const float WINDOW_EXTEND = 1.0f;

	static const int boxWidth = WIDTHSMALL;
	static const int boxHeight = HEIGHTSMALL;
	static const int startX = (int)(WIDTH * 0.5f - boxWidth * 0.5f * WINDOW_EXTEND);
	static const int startY = (int)(HEIGHT * 0.3f - boxHeight * 0.3f * WINDOW_EXTEND);
	static const int endX = startX + (int)(boxWidth * WINDOW_EXTEND);
	static const int endY = startY + (int)(boxHeight * WINDOW_EXTEND);
};

