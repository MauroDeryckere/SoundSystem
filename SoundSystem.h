#ifndef SOUNDSYSTEM
#define SOUNDSYSTEM

#include <filesystem>
#include <string>

namespace Internal
{
	class SoundSystem
	{
	public:
		SoundSystem() noexcept = default;
		virtual ~SoundSystem() noexcept = default;

		virtual void Update() noexcept = 0;

		[[nodiscard]] virtual std::filesystem::path const& GetDataPath() const noexcept = 0;

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

		std::filesystem::path const& GetDataPath() const noexcept { return m_DataPath; }

	private:
		std::filesystem::path const m_DataPath{ "NullSoundSystem DataPath" };
	};
}

#endif