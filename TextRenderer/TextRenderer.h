#pragma once

#include <ft2build.h>
#include <map>
#include <iostream>
#include <GL/glew.h>

#include FT_FREETYPE_H
#include FT_TRUETYPE_IDS_H

const std::wstring SPECIAL =
{
  L"<>,./|\:!@#$%^&*()-=+~`[]{} "
};

const std::wstring DIGITS =
{
  L"1234567890"
};

const std::wstring LANG_SYMBOLS[2] =
{
  L"ABCDEFGHIJKLMNOPQRSTVUWXYZabcdefghijklmnopqrstvuwxyz",
  L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХКЧШЩЪЬЫЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"
};

struct Character
{
  unsigned TextureID; // ID handle of the glyph texture
  unsigned int width, rows; // Size of glyph
  signed int bitmap_left, bitmap_top; // Offset from baseline to left/top of glyph
  unsigned Advance; // Horizontal offset to advance to next glyph
};

class TextRenderer
{
  private:
    std::map<long, Character> Characters;
    char info_log[512];
    int symbol_height;

    void LoadGlyph(FT_Face face, const std::wstring unicode_symbols);

  public:
    /* Draw text with generate buffer */
    void PrintTextToBlock(std::wstring text, float scale);
    void PrintTextToScreen(std::wstring text, float scale, float x, float y);
    float getTextWidth(std::wstring text, float scale);
    void PrintChar(const GLubyte symbol, float scale, float x, float y);
    void PrintAllChars(float scale, float width, float x, float y);
    TextRenderer(int size, const char* file_path, unsigned lang);
    char* getInfoLog();
    int getSymbolHeight();

    ~TextRenderer();
};
