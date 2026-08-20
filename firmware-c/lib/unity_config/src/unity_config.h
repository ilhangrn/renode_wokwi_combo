#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

/* Minimal Unity configuration for PlatformIO embedded targets.
 * The test runner (test_sum.cpp) provides unity_output_char() to send output.
 */

#ifdef __cplusplus
extern "C"
{
#endif

    void unity_output_char(char c);

#ifdef __cplusplus
}
#endif

#define UNITY_OUTPUT_CHAR(c) unity_output_char((char)(c))
#define UNITY_OUTPUT_FLUSH() \
    do                       \
    {                        \
    } while (0)
#define UNITY_OUTPUT_START() \
    do                       \
    {                        \
    } while (0)
#define UNITY_OUTPUT_COMPLETE() \
    do                          \
    {                           \
    } while (0)

#endif /* UNITY_CONFIG_H */
