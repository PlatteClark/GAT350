#include "Font.h" 
#include <SDL_ttf.h> 

namespace squampernaut
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont != NULL)
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Create( std::string filename, ... )
	{
		va_list args;
		va_start(args, filename);

		int t = va_arg(args, int );

		va_end(args);
		return Load(filename, t );
	}

	bool Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);

		return m_ttfFont;
	}
}