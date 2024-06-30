#ifndef SOUNDSYSTEM
#define SOUNDSYSTEM

#include <filesystem>
#include <string>

namespace Internal
{
	struct SoundData;

	class SoundSystem
	{
	public:
		SoundSystem() noexcept = default;
		virtual ~SoundSystem() noexcept = default;

		virtual void Update() noexcept = 0;

		[[nodiscard]] virtual std::filesystem::path const& GetDataPath() const noexcept = 0;

		virtual bool LoadSound(SoundData const& soundData) noexcept = 0;
		virtual bool UnloadSound(std::string_view sound) noexcept = 0;

		SoundSystem(const SoundSystem&) = delete;
		SoundSystem& operator=(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator=(SoundSystem&&) = delete;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() noexcept = default;
		~NullSoundSystem() noexcept = default;

		void Update() noexcept {}

		[[nodiscard]] std::filesystem::path const& GetDataPath() const noexcept { return m_DataPath; }

		bool LoadSound(SoundData const&) noexcept { return false; }
		bool UnloadSound(std::string_view) noexcept { return false;  }

	private:
		std::filesystem::path const m_DataPath{ "NullSoundSystem DataPath" };
	};
}

#endif