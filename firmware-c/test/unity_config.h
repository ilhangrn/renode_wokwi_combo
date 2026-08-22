#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

    void unity_output_char(char character);

#ifdef __cplusplus
}
#endif

#define UNITY_OUTPUT_CHAR(character) unity_output_char((char)(character))
#define UNITY_OUTPUT_FLUSH()
#define UNITY_OUTPUT_START()
#define UNITY_OUTPUT_COMPLETE()

#endif