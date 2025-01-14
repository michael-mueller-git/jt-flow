#pragma once

typedef void* FlowHandle;
typedef void(*DrawCallback)(void* data, int width, int height, void* userData);
typedef void(*LoggingCallback)(int level, const char* message);
typedef void(*FlowRunCallback)(FlowHandle handle, int frame_number);

typedef unsigned long FrameNumber;
typedef struct FrameRange {
    FrameNumber fromFrame;
    FrameNumber toFrame;
} FrameRange;

typedef struct FlowProperties {
    int numberOfPools;
    float maxValue;
    bool overlayHalf;
    float focusPoint;
    float focusSize;
    float waveSmoothing1;
} FlowProperties;

#ifdef _WIN32
#ifdef FLOWLIB_IMPORT
#define FLOWLIB_API __declspec(dllimport)
#else
#define FLOWLIB_API __declspec(dllexport)
#endif
#else
#define FLOWLIB_API
#endif

FLOWLIB_API FlowHandle FlowCreateHandle(const char* videoPath, FlowProperties* properties);
FLOWLIB_API bool FlowDestroyHandle(FlowHandle handle);
FLOWLIB_API bool FlowSetLogger(LoggingCallback callback);
FLOWLIB_API bool FlowRun(FlowHandle handle, FlowRunCallback callback, int callbackInterval);

FLOWLIB_API FrameNumber FlowGetLength(FlowHandle handle);
FLOWLIB_API FrameNumber FlowGetLengthMs(FlowHandle handle);
FLOWLIB_API bool FlowDrawRange(FlowHandle handle, FrameRange range, DrawCallback callback, void* userData);
FLOWLIB_API bool FlowCalcWave(FlowHandle handle, FrameRange range, DrawCallback callback, void* userData);
FLOWLIB_API float FlowProgress(FlowHandle handle);
FLOWLIB_API bool FlowSave(FlowHandle handle, const char* path);
FLOWLIB_API char* FlowLastError();
