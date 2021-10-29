#include <iostream>
#include <string>

#include "Enigma/Enigma.h"

int main(int argc, char* argv[]) {
	// Enigma initialize with default settings (plugboard, 3 rotors, reflector)
	Encryption::Enigma enigma;

	try {
		enigma.Init("Rotors/", "Reflectors/");
	}
	catch (const char* error) {
		std::cout << error << std::endl;
		return -1;
	}

	// ========================================================================================= //

	if (argc == 1) {
		std::cout << "Loading default settings...\n";

		// Set plugboard
		enigma.AddPlugboardConnection("AM");
		enigma.AddPlugboardConnection("JD");
		enigma.AddPlugboardConnection("EZ");
		enigma.AddPlugboardConnection("PL");
		enigma.AddPlugboardConnection("GR");
		enigma.AddPlugboardConnection("OK");

		// Set number of rotors
		enigma.SetRotorCount(5);

		// Set rotor names
		enigma.SetRotorName(0, "I");
		enigma.SetRotorName(1, "II");
		enigma.SetRotorName(2, "III");
		enigma.SetRotorName(3, "II");
		enigma.SetRotorName(4, "I");

		// Set rotor keys
		enigma.SetRotorKey(0, 'C');
		enigma.SetRotorKey(1, 'L');
		enigma.SetRotorKey(2, 'O');
		enigma.SetRotorKey(3, 'C');
		enigma.SetRotorKey(4, 'K');

		// Set rotor rings
		enigma.SetRotorRing(0, 7);
		enigma.SetRotorRing(1, 11);
		enigma.SetRotorRing(2, 25);
		enigma.SetRotorRing(3, 18);
		enigma.SetRotorRing(4, 2);

		// Set reflector
		enigma.SetReflector("B");
	}
	else {
		std::cout << "Loading settings from file...\n";

		// Load settings from file
		std::string password = "Password!";
		enigma.LoadSettings(argv[1], password);

		// Set rotor keys
		enigma.SetRotorKey(0, 'C');
		enigma.SetRotorKey(1, 'L');
		enigma.SetRotorKey(2, 'O');
		enigma.SetRotorKey(3, 'C');
		enigma.SetRotorKey(4, 'K');
	}

	// Encrypt message
	std::string message = "TEST MESSAGE";
	enigma.EncryptMessage(message);

	// Print encrypted message
	std::string encrypted_message = enigma.GetMessage().Output;
	std::cout << "Encrypted: " << encrypted_message << std::endl;

	// Decrypt message by encrypting it again
	enigma.EncryptMessage(encrypted_message);

	// Print decrypted message
	std::string decrypted_message1 = enigma.GetMessage().Output;
	std::cout << "Decrypted: " << decrypted_message1 << std::endl;

	// Save current settings
	std::string password = "Password!";
	enigma.SaveSettings("Settings/TEST.stg", password);

	return 0;
}