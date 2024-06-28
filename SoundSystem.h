#ifndef SOUNDSYSTEM
#define SOUNDSYSTEM

#include <string>

namespace Internal
{
	class SoundSystem
	{
	public:
		SoundSystem() noexcept = default;
		virtual ~SoundSystem() noexcept = default;

		virtual void Update() noexcept = 0;

		[[nodiscard]] virtual std::string_view GetDataPath() const noexcept = 0;

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

		std::string_view GetDataPath() const noexcept { return "NullSoundSystem DataPath"; }
	};
}

#endif