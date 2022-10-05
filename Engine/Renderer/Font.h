#pragma once 
// !! add necessary includes 
#include <string>
#include "../Resource/Resource.h"

struct _TTF_Font;

namespace squampernaut
{

	class Font : public Resource
	{

	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(std::string filename, ... ) override;

		bool Load(const std::string& filename, int fontSize);


		friend class Text;
	private:

		_TTF_Font* m_ttfFont{nullptr};
	};
}