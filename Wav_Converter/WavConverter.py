import wave
import numpy as np

# Load the .wav file
input_wav = "../Assets/Audio_Files/audioGoAhead/Go_Ahead_8K_Sample.wav"
output_c = "../Assets/Audio_Files/audioGoAhead/audioGoAhead.c"

# Open the .wav file
with wave.open(input_wav, "rb") as wav:
    n_channels = wav.getnchannels()
    sample_width = wav.getsampwidth()
    frame_rate = wav.getframerate()
    n_frames = wav.getnframes()

    # Read frames
    frames = wav.readframes(n_frames)

    # Convert to numpy array (signed PCM)
    dtype = np.int16 if sample_width == 2 else np.int8
    audio_data = np.frombuffer(frames, dtype=dtype)

    # Promote to a larger type to prevent overflow during arithmetic
    audio_data = audio_data.astype(np.int32)

    # Normalize to unsigned 8-bit (uint8_t)
    if dtype == np.int16:
        audio_data = ((audio_data + 32768) // 256).astype(np.uint8)
    else:
        audio_data = (audio_data + 128).astype(np.uint8)

    # Write as a C array
    with open(output_c, "w") as c_file:
        c_file.write("#include <stdint.h>\n\n")
        c_file.write(f"const uint8_t audio_data[] = {{\n")
        c_file.write(", ".join(map(str, audio_data)))
        c_file.write("\n};\n")
        c_file.write(f"const size_t audio_data_len = {len(audio_data)};\n")

print(f"Unsigned char array written to {output_c}")