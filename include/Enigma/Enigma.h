#pragma once
#define MAX_ROTOR_COUNT 16

#include "Enigma/Plugboard.h"
#include "Enigma/Reflector.h"
#include "Enigma/Rotor.h"

#include <vector>
#include <memory>

namespace Encryption {

	struct Components {
		struct AvailableComponents {
			std::vector<Rotor> Rotors;
			std::vector<Reflector> Reflectors;
		} Available;		// Components available - can be used for decryption

		struct ConfigurationComponents {
			std::vector<Rotor> Rotors;
			std::unique_ptr<Reflector> Reflector;
		} Configuration;	// Components with configuration - currently used for decryption
	};

	struct Message {
		std::string Input;
		std::string Output;
	};

	class Enigma {
	public:
		Enigma();
		void Init(const std::string& rotor_dir, const std::string& reflector_dir);

		void LoadSettings(const std::string& filepath, const std::string& password);
		void SaveSettings(const std::string& filepath, const std::string& password) const;

		void AddPlugboardConnection(const std::string& plugs);
		void RemovePlugboardConnection(const std::string& plugs);
		
		void SetRotorCount(int count);
		void SetReflector(const std::string& name);

		void SetRotorName(int index, const std::string& name);
		void SetRotorRing(int index, int ring);
		void SetRotorKey(int index, char key);

		void EncryptMessage(const std::string& message);

		inline std::string GetConnectedPlugs() const { return m_Plugboard->GetConnectedPlugs(); }
		inline const std::string& GetRotorKeySettings() const { return m_RotorConfigurationCache[0]; }

		inline const Components& GetComponents() const { return m_Components; }
		inline const Message& GetMessage() const { return m_Message; }
	private:
		void InitRotors(const std::string& dir);
		void InitReflectors(const std::string& dir);

		void AddLetter(char letter);
		bool ShouldAdjacentRotorMove(int index) const;

		void EncryptMessageAfterConfigurationChanges();
	private:
		// Decryption components
		std::unique_ptr<Plugboard> m_Plugboard;
		Components m_Components;

		// Rotor cache
		std::vector<std::string> m_RotorConfigurationCache;
		int m_RotorConfigurationCacheLastIndex;

		// Encrypted and decrypted message
		Message m_Message;
	};

}