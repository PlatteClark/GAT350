#pragma once

namespace FMOD
{
	// !! forward declare FMOD Channel 
	class Channel;
}

namespace squampernaut
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel( FMOD::Channel* channel ) ; // !! set m_channel 

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);

		float GetPitch();

		void SetVolume(float volume);

		float GetVolume();



		// !! create SetPitch/GetPitch (takes float, returns float) 
		// !! create SetVolume/GetVolume (takes float, returns float) 

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}