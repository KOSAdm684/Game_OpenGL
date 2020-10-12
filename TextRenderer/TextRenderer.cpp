#include "TextRenderer.h"

void TextRenderer::LoadGlyph(FT_Face face, const std::wstring unicode_symbols)
{
  std::wstring::const_iterator c;

  for (c = unicode_symbols.begin(); c != unicode_symbols.end(); ++c)
  {
    // Load character glyph
    long code = *c;

    if (FT_Load_Char(face, code, FT_LOAD_RENDER))
    {
      strcpy(info_log, "ERROR::FREETYTPE: Failed to load Glyph");
      continue;
    }

    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Now store character for later use
    Character character = {
      texture,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      face->glyph->bitmap_left,
      face->glyph->bitmap_top,
      face->glyph->advance.x
    };

    Characters.insert(std::pair<long, Character>(code, character));
  }
}

TextRenderer::TextRenderer(int size, const char* file_path, unsigned lang)
{
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
    strcpy(info_log, "ERROR::FREETYPE: Could not init FreeType Library");
  }

  FT_Face face;
  if (FT_New_Face(ft, file_path, 0, &face))
  {
    strcpy(info_log, "ERROR::FREETYPE: Failed to load font");
  }

  FT_Set_Pixel_Sizes(face, 0, size);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  LoadGlyph(face, DIGITS);
  LoadGlyph(face, SPECIAL);

  LoadGlyph(face, LANG_SYMBOLS[0]);
  LoadGlyph(face, LANG_SYMBOLS[1]);

  glBindTexture(GL_TEXTURE_2D, 0);

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  symbol_height = size;
}

void TextRenderer::PrintTextToBlock(std::wstring text, float scale)
{
  // Iterate through all characters
  std::wstring::const_iterator c;

  float x = 0;
  float y = 0;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];

    GLfloat xpos = x + ch.bitmap_left * scale;
    GLfloat ypos = y - (ch.rows - ch.bitmap_top) * scale;

    GLfloat w = ch.width * scale;
    GLfloat h = ch.rows * scale;

    // Update VBO for each character
    GLfloat vertices[6][4] = {
    { xpos, ypos + h, 0.0, 0.0 },
    { xpos, ypos, 0.0, 1.0 },
    { xpos + w, ypos, 1.0, 1.0 },

    { xpos, ypos + h, 0.0, 0.0 },
    { xpos + w, ypos, 1.0, 1.0 },
    { xpos + w, ypos + h, 1.0, 0.0 }
    };

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

    // Update content of VBO memory
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
  }
}

void TextRenderer::PrintTextToScreen(std::wstring text, float scale, float _x, float _y)
{
  // Iterate through all characters
  std::wstring::const_iterator c;

  float x = _x;
  float y = _y;

  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];

    GLfloat xpos = x + ch.bitmap_left * scale;
    GLfloat ypos = y - (ch.rows - ch.bitmap_top) * scale;

    GLfloat w = ch.width * scale;
    GLfloat h = ch.rows * scale;

    // Update VBO for each character
    GLfloat vertices[6][4] = {
    { xpos, ypos + h, 0.0, 0.0 },
    { xpos, ypos, 0.0, 1.0 },
    { xpos + w, ypos, 1.0, 1.0 },

    { xpos, ypos + h, 0.0, 0.0 },
    { xpos + w, ypos, 1.0, 1.0 },
    { xpos + w, ypos + h, 1.0, 0.0 }
    };

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

    // Update content of VBO memory
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.Advance>>6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
  }
}

void TextRenderer::PrintChar(const GLubyte symbol, float scale, float _x, float _y)
{
  Character ch = Characters[symbol];

  GLfloat xpos = _x + ch.bitmap_left * scale;
  GLfloat ypos = _y - (ch.rows - ch.bitmap_top) * scale;

  GLfloat w = ch.width * scale;
  GLfloat h = ch.rows * scale;

  // Update VBO for each character
  GLfloat vertices[6][4] = {
  { xpos, ypos + h, 0.0, 0.0 },
  { xpos, ypos, 0.0, 1.0 },
  { xpos + w, ypos, 1.0, 1.0 },

  { xpos, ypos + h, 0.0, 0.0 },
  { xpos + w, ypos, 1.0, 1.0 },
  { xpos + w, ypos + h, 1.0, 0.0 }
  };

  // Render glyph texture over quad
  glBindTexture(GL_TEXTURE_2D, ch.TextureID);

  // Update content of VBO memory
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

  // Render quad
  glDrawArrays(GL_TRIANGLES, 0, 6);
  }

void TextRenderer::PrintAllChars(float scale, float width, float _x, float _y)
{
  // Iterate through all characters\

  float x = _x;
  float y = _y;

  long count = 200;

  for (long c = 0; c < count; ++c)
  {
    Character ch = Characters[c];

    GLfloat xpos = x + ch.bitmap_left * scale;
    GLfloat ypos = y - (ch.rows - ch.bitmap_top) * scale;

    GLfloat w = ch.width * scale;
    GLfloat h = ch.rows * scale;

    // Update VBO for each character
    GLfloat vertices[6][4] = {
    { xpos, ypos + h, 0.0, 0.0 },
    { xpos, ypos, 0.0, 1.0 },
    { xpos + w, ypos, 1.0, 1.0 },

    { xpos, ypos + h, 0.0, 0.0 },
    { xpos + w, ypos, 1.0, 1.0 },
    { xpos + w, ypos + h, 1.0, 0.0 }
    };

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

    // Update content of VBO memory
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.Advance>>6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

    if (x > _x + width)
    {
      x = _x;
      y -= symbol_height * scale;
    }
  }
}

float TextRenderer::getTextWidth(std::wstring text, float scale)
{
  std::wstring::const_iterator c;

  float x = 0;
  float width = 0;

  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];
    GLfloat w = ch.width * scale;

    x += (ch.Advance>>6) * scale;
    width = x + w;
  }

  return width;
}

TextRenderer::~TextRenderer()
{
  std::map<long, Character>::const_iterator iterator;

  for (iterator = Characters.begin(); iterator != Characters.end(); ++iterator)
  {
    glDeleteTextures(1, &(iterator->second.TextureID));
  }

  this->Characters.clear();
}

char* TextRenderer::getInfoLog()
{
  return info_log;
}

int TextRenderer::getSymbolHeight()
{
  return symbol_height;
}
