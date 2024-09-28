
// GPUTmpGUIDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GPUTmpGUI.h"
#include "GPUTmpGUIDlg.h"
#include "afxdialogex.h"
#include "windows.h"
#include "malloc.h"
#include "setupapi.h"
#include "nvme.h"
#pragma comment(lib, "setupapi.lib") 


typedef enum _NvAPI_Status
{
    NVAPI_OK = 0,      //!< Success. Request is completed.
    NVAPI_ERROR = -1,      //!< Generic error
    NVAPI_LIBRARY_NOT_FOUND = -2,      //!< NVAPI support library cannot be loaded.
    NVAPI_NO_IMPLEMENTATION = -3,      //!< not implemented in current driver installation
    NVAPI_API_NOT_INITIALIZED = -4,      //!< NvAPI_Initialize has not been called (successfully)
    NVAPI_INVALID_ARGUMENT = -5,      //!< The argument/parameter value is not valid or NULL.
    NVAPI_NVIDIA_DEVICE_NOT_FOUND = -6,      //!< No NVIDIA display driver, or NVIDIA GPU driving a display, was found.
    NVAPI_END_ENUMERATION = -7,      //!< No more items to enumerate
    NVAPI_INVALID_HANDLE = -8,      //!< Invalid handle
    NVAPI_INCOMPATIBLE_STRUCT_VERSION = -9,      //!< An argument's structure version is not supported
    NVAPI_HANDLE_INVALIDATED = -10,     //!< The handle is no longer valid (likely due to GPU or display re-configuration)
    NVAPI_OPENGL_CONTEXT_NOT_CURRENT = -11,     //!< No NVIDIA OpenGL context is current (but needs to be)
    NVAPI_INVALID_POINTER = -14,     //!< An invalid pointer, usually NULL, was passed as a parameter
    NVAPI_NO_GL_EXPERT = -12,     //!< OpenGL Expert is not supported by the current drivers
    NVAPI_INSTRUMENTATION_DISABLED = -13,     //!< OpenGL Expert is supported, but driver instrumentation is currently disabled
    NVAPI_NO_GL_NSIGHT = -15,     //!< OpenGL does not support Nsight

    NVAPI_EXPECTED_LOGICAL_GPU_HANDLE = -100,    //!< Expected a logical GPU handle for one or more parameters
    NVAPI_EXPECTED_PHYSICAL_GPU_HANDLE = -101,    //!< Expected a physical GPU handle for one or more parameters
    NVAPI_EXPECTED_DISPLAY_HANDLE = -102,    //!< Expected an NV display handle for one or more parameters
    NVAPI_INVALID_COMBINATION = -103,    //!< The combination of parameters is not valid. 
    NVAPI_NOT_SUPPORTED = -104,    //!< Requested feature is not supported in the selected GPU
    NVAPI_PORTID_NOT_FOUND = -105,    //!< No port ID was found for the I2C transaction
    NVAPI_EXPECTED_UNATTACHED_DISPLAY_HANDLE = -106,    //!< Expected an unattached display handle as one of the input parameters.
    NVAPI_INVALID_PERF_LEVEL = -107,    //!< Invalid perf level 
    NVAPI_DEVICE_BUSY = -108,    //!< Device is busy; request not fulfilled
    NVAPI_NV_PERSIST_FILE_NOT_FOUND = -109,    //!< NV persist file is not found
    NVAPI_PERSIST_DATA_NOT_FOUND = -110,    //!< NV persist data is not found
    NVAPI_EXPECTED_TV_DISPLAY = -111,    //!< Expected a TV output display
    NVAPI_EXPECTED_TV_DISPLAY_ON_DCONNECTOR = -112,    //!< Expected a TV output on the D Connector - HDTV_EIAJ4120.
    NVAPI_NO_ACTIVE_SLI_TOPOLOGY = -113,    //!< SLI is not active on this device.
    NVAPI_SLI_RENDERING_MODE_NOTALLOWED = -114,    //!< Setup of SLI rendering mode is not possible right now.
    NVAPI_EXPECTED_DIGITAL_FLAT_PANEL = -115,    //!< Expected a digital flat panel.
    NVAPI_ARGUMENT_EXCEED_MAX_SIZE = -116,    //!< Argument exceeds the expected size.
    NVAPI_DEVICE_SWITCHING_NOT_ALLOWED = -117,    //!< Inhibit is ON due to one of the flags in NV_GPU_DISPLAY_CHANGE_INHIBIT or SLI active.
    NVAPI_TESTING_CLOCKS_NOT_SUPPORTED = -118,    //!< Testing of clocks is not supported.
    NVAPI_UNKNOWN_UNDERSCAN_CONFIG = -119,    //!< The specified underscan config is from an unknown source (e.g. INF)
    NVAPI_TIMEOUT_RECONFIGURING_GPU_TOPO = -120,    //!< Timeout while reconfiguring GPUs
    NVAPI_DATA_NOT_FOUND = -121,    //!< Requested data was not found
    NVAPI_EXPECTED_ANALOG_DISPLAY = -122,    //!< Expected an analog display
    NVAPI_NO_VIDLINK = -123,    //!< No SLI video bridge is present
    NVAPI_REQUIRES_REBOOT = -124,    //!< NVAPI requires a reboot for the settings to take effect
    NVAPI_INVALID_HYBRID_MODE = -125,    //!< The function is not supported with the current Hybrid mode.
    NVAPI_MIXED_TARGET_TYPES = -126,    //!< The target types are not all the same
    NVAPI_SYSWOW64_NOT_SUPPORTED = -127,    //!< The function is not supported from 32-bit on a 64-bit system.
    NVAPI_IMPLICIT_SET_GPU_TOPOLOGY_CHANGE_NOT_ALLOWED = -128,    //!< There is no implicit GPU topology active. Use NVAPI_SetHybridMode to change topology.
    NVAPI_REQUEST_USER_TO_CLOSE_NON_MIGRATABLE_APPS = -129,      //!< Prompt the user to close all non-migratable applications.    
    NVAPI_OUT_OF_MEMORY = -130,    //!< Could not allocate sufficient memory to complete the call.
    NVAPI_WAS_STILL_DRAWING = -131,    //!< The previous operation that is transferring information to or from this surface is incomplete.
    NVAPI_FILE_NOT_FOUND = -132,    //!< The file was not found.
    NVAPI_TOO_MANY_UNIQUE_STATE_OBJECTS = -133,    //!< There are too many unique instances of a particular type of state object.
    NVAPI_INVALID_CALL = -134,    //!< The method call is invalid. For example, a method's parameter may not be a valid pointer.
    NVAPI_D3D10_1_LIBRARY_NOT_FOUND = -135,    //!< d3d10_1.dll cannot be loaded.
    NVAPI_FUNCTION_NOT_FOUND = -136,    //!< Couldn't find the function in the loaded DLL.
    NVAPI_INVALID_USER_PRIVILEGE = -137,    //!< Current User is not Admin.
    NVAPI_EXPECTED_NON_PRIMARY_DISPLAY_HANDLE = -138,    //!< The handle corresponds to GDIPrimary.
    NVAPI_EXPECTED_COMPUTE_GPU_HANDLE = -139,    //!< Setting Physx GPU requires that the GPU is compute-capable.
    NVAPI_STEREO_NOT_INITIALIZED = -140,    //!< The Stereo part of NVAPI failed to initialize completely. Check if the stereo driver is installed.
    NVAPI_STEREO_REGISTRY_ACCESS_FAILED = -141,    //!< Access to stereo-related registry keys or values has failed.
    NVAPI_STEREO_REGISTRY_PROFILE_TYPE_NOT_SUPPORTED = -142, //!< The given registry profile type is not supported.
    NVAPI_STEREO_REGISTRY_VALUE_NOT_SUPPORTED = -143,    //!< The given registry value is not supported.
    NVAPI_STEREO_NOT_ENABLED = -144,    //!< Stereo is not enabled and the function needed it to execute completely.
    NVAPI_STEREO_NOT_TURNED_ON = -145,    //!< Stereo is not turned on and the function needed it to execute completely.
    NVAPI_STEREO_INVALID_DEVICE_INTERFACE = -146,    //!< Invalid device interface.
    NVAPI_STEREO_PARAMETER_OUT_OF_RANGE = -147,    //!< Separation percentage or JPEG image capture quality is out of [0-100] range.
    NVAPI_STEREO_FRUSTUM_ADJUST_MODE_NOT_SUPPORTED = -148, //!< The given frustum adjust mode is not supported.
    NVAPI_TOPO_NOT_POSSIBLE = -149,    //!< The mosaic topology is not possible given the current state of the hardware.
    NVAPI_MODE_CHANGE_FAILED = -150,    //!< An attempt to do a display resolution mode change has failed.        
    NVAPI_D3D11_LIBRARY_NOT_FOUND = -151,    //!< d3d11.dll/d3d11_beta.dll cannot be loaded.
    NVAPI_INVALID_ADDRESS = -152,    //!< Address is outside of valid range.
    NVAPI_STRING_TOO_SMALL = -153,    //!< The pre-allocated string is too small to hold the result.
    NVAPI_MATCHING_DEVICE_NOT_FOUND = -154,    //!< The input does not match any of the available devices.
    NVAPI_DRIVER_RUNNING = -155,    //!< Driver is running.
    NVAPI_DRIVER_NOTRUNNING = -156,    //!< Driver is not running.
    NVAPI_ERROR_DRIVER_RELOAD_REQUIRED = -157,    //!< A driver reload is required to apply these settings.
    NVAPI_SET_NOT_ALLOWED = -158,    //!< Intended setting is not allowed.
    NVAPI_ADVANCED_DISPLAY_TOPOLOGY_REQUIRED = -159,    //!< Information can't be returned due to "advanced display topology".
    NVAPI_SETTING_NOT_FOUND = -160,    //!< Setting is not found.
    NVAPI_SETTING_SIZE_TOO_LARGE = -161,    //!< Setting size is too large.
    NVAPI_TOO_MANY_SETTINGS_IN_PROFILE = -162,    //!< There are too many settings for a profile. 
    NVAPI_PROFILE_NOT_FOUND = -163,    //!< Profile is not found.
    NVAPI_PROFILE_NAME_IN_USE = -164,    //!< Profile name is duplicated.
    NVAPI_PROFILE_NAME_EMPTY = -165,    //!< Profile name is empty.
    NVAPI_EXECUTABLE_NOT_FOUND = -166,    //!< Application not found in the Profile.
    NVAPI_EXECUTABLE_ALREADY_IN_USE = -167,    //!< Application already exists in the other profile.
    NVAPI_DATATYPE_MISMATCH = -168,    //!< Data Type mismatch 
    NVAPI_PROFILE_REMOVED = -169,    //!< The profile passed as parameter has been removed and is no longer valid.
    NVAPI_UNREGISTERED_RESOURCE = -170,    //!< An unregistered resource was passed as a parameter. 
    NVAPI_ID_OUT_OF_RANGE = -171,    //!< The DisplayId corresponds to a display which is not within the normal outputId range.
    NVAPI_DISPLAYCONFIG_VALIDATION_FAILED = -172,    //!< Display topology is not valid so the driver cannot do a mode set on this configuration.
    NVAPI_DPMST_CHANGED = -173,    //!< Display Port Multi-Stream topology has been changed.
    NVAPI_INSUFFICIENT_BUFFER = -174,    //!< Input buffer is insufficient to hold the contents.    
    NVAPI_ACCESS_DENIED = -175,    //!< No access to the caller.
    NVAPI_MOSAIC_NOT_ACTIVE = -176,    //!< The requested action cannot be performed without Mosaic being enabled.
    NVAPI_SHARE_RESOURCE_RELOCATED = -177,    //!< The surface is relocated away from video memory.
    NVAPI_REQUEST_USER_TO_DISABLE_DWM = -178,    //!< The user should disable DWM before calling NvAPI.
    NVAPI_D3D_DEVICE_LOST = -179,    //!< D3D device status is D3DERR_DEVICELOST or D3DERR_DEVICENOTRESET - the user has to reset the device.
    NVAPI_INVALID_CONFIGURATION = -180,    //!< The requested action cannot be performed in the current state.
    NVAPI_STEREO_HANDSHAKE_NOT_DONE = -181,    //!< Call failed as stereo handshake not completed.
    NVAPI_EXECUTABLE_PATH_IS_AMBIGUOUS = -182,    //!< The path provided was too short to determine the correct NVDRS_APPLICATION
    NVAPI_DEFAULT_STEREO_PROFILE_IS_NOT_DEFINED = -183,    //!< Default stereo profile is not currently defined
    NVAPI_DEFAULT_STEREO_PROFILE_DOES_NOT_EXIST = -184,    //!< Default stereo profile does not exist
    NVAPI_CLUSTER_ALREADY_EXISTS = -185,    //!< A cluster is already defined with the given configuration.
    NVAPI_DPMST_DISPLAY_ID_EXPECTED = -186,    //!< The input display id is not that of a multi stream enabled connector or a display device in a multi stream topology 
    NVAPI_INVALID_DISPLAY_ID = -187,    //!< The input display id is not valid or the monitor associated to it does not support the current operation
    NVAPI_STREAM_IS_OUT_OF_SYNC = -188,    //!< While playing secure audio stream, stream goes out of sync
    NVAPI_INCOMPATIBLE_AUDIO_DRIVER = -189,    //!< Older audio driver version than required
    NVAPI_VALUE_ALREADY_SET = -190,    //!< Value already set, setting again not allowed.
    NVAPI_TIMEOUT = -191,    //!< Requested operation timed out 
    NVAPI_GPU_WORKSTATION_FEATURE_INCOMPLETE = -192,    //!< The requested workstation feature set has incomplete driver internal allocation resources
    NVAPI_STEREO_INIT_ACTIVATION_NOT_DONE = -193,    //!< Call failed because InitActivation was not called.
    NVAPI_SYNC_NOT_ACTIVE = -194,    //!< The requested action cannot be performed without Sync being enabled.
    NVAPI_SYNC_MASTER_NOT_FOUND = -195,    //!< The requested action cannot be performed without Sync Master being enabled.
    NVAPI_INVALID_SYNC_TOPOLOGY = -196,    //!< Invalid displays passed in the NV_GSYNC_DISPLAY pointer.
    NVAPI_ECID_SIGN_ALGO_UNSUPPORTED = -197,    //!< The specified signing algorithm is not supported. Either an incorrect value was entered or the current installed driver/hardware does not support the input value.
    NVAPI_ECID_KEY_VERIFICATION_FAILED = -198,    //!< The encrypted public key verification has failed.
} NvAPI_Status;
HMODULE hmodNvapi = NULL;
#define NVAPI_MAX_PHYSICAL_GPUS             64
#define NVAPI_INTERFACE extern __success(return == NVAPI_OK) NvAPI_Status __cdecl
typedef enum
{
    NVAPI_THERMAL_TARGET_NONE = 0,
    NVAPI_THERMAL_TARGET_GPU = 1,     //!< GPU core temperature requires NvPhysicalGpuHandle
    NVAPI_THERMAL_TARGET_MEMORY = 2,     //!< GPU memory temperature requires NvPhysicalGpuHandle
    NVAPI_THERMAL_TARGET_POWER_SUPPLY = 4,     //!< GPU power supply temperature requires NvPhysicalGpuHandle
    NVAPI_THERMAL_TARGET_BOARD = 8,     //!< GPU board ambient temperature requires NvPhysicalGpuHandle
    NVAPI_THERMAL_TARGET_VCD_BOARD = 9,     //!< Visual Computing Device Board temperature requires NvVisualComputingDeviceHandle
    NVAPI_THERMAL_TARGET_VCD_INLET = 10,    //!< Visual Computing Device Inlet temperature requires NvVisualComputingDeviceHandle
    NVAPI_THERMAL_TARGET_VCD_OUTLET = 11,    //!< Visual Computing Device Outlet temperature requires NvVisualComputingDeviceHandle

    NVAPI_THERMAL_TARGET_ALL = 15,
    NVAPI_THERMAL_TARGET_UNKNOWN = -1,
} NV_THERMAL_TARGET;
typedef enum
{
    NVAPI_THERMAL_CONTROLLER_NONE = 0,
    NVAPI_THERMAL_CONTROLLER_GPU_INTERNAL,
    NVAPI_THERMAL_CONTROLLER_ADM1032,
    NVAPI_THERMAL_CONTROLLER_MAX6649,
    NVAPI_THERMAL_CONTROLLER_MAX1617,
    NVAPI_THERMAL_CONTROLLER_LM99,
    NVAPI_THERMAL_CONTROLLER_LM89,
    NVAPI_THERMAL_CONTROLLER_LM64,
    NVAPI_THERMAL_CONTROLLER_ADT7473,
    NVAPI_THERMAL_CONTROLLER_SBMAX6649,
    NVAPI_THERMAL_CONTROLLER_VBIOSEVT,
    NVAPI_THERMAL_CONTROLLER_OS,
    NVAPI_THERMAL_CONTROLLER_UNKNOWN = -1,
} NV_THERMAL_CONTROLLER;
#define NVAPI_MAX_THERMAL_SENSORS_PER_GPU 3
typedef struct
{
    DWORD   version;                //!< structure version
    DWORD   count;                  //!< number of associated thermal sensors
    struct
    {
        NV_THERMAL_CONTROLLER       controller;         //!< internal, ADM1032, MAX6649...
        signed int                       defaultMinTemp;     //!< Minimum default temperature value of the thermal sensor in degree Celsius
        signed int                       defaultMaxTemp;     //!< Maximum default temperature value of the thermal sensor in degree Celsius
        signed int                       currentTemp;        //!< Current temperature value of the thermal sensor in degree Celsius
        NV_THERMAL_TARGET           target;             //!< Thermal sensor targeted - GPU, memory, chipset, powersupply, Visual Computing Device, etc
    } sensor[NVAPI_MAX_THERMAL_SENSORS_PER_GPU];

} NV_GPU_THERMAL_SETTINGS;


//total size 0xAB0

typedef struct _NV_API_TEMP_INDEX {
    DWORD Version;
    DWORD QueryTempIndex;
    BYTE Unknown[0xAA1];

    BYTE GpuHotspotTempIndex;
    BYTE Unknown2;
    BYTE MemoryTempIndex;
    BYTE Unknown3[4];
}NV_API_TEMP_INDEX, * PNV_API_TEMP_INDEX;

//total size 0xA8

typedef struct _NV_API_ADV_TEMPERATURE {
    DWORD Version;
    DWORD QueryTempIndex;

    BYTE Unknown[0x20];

    DWORD TempTable[32];

}NV_API_ADV_TEMPERATURE, * PNV_API_ADV_TEMPERATURE;


#define NVAPI_SHORT_STRING_MAX      64

typedef char NvAPI_ShortString[NVAPI_SHORT_STRING_MAX];

typedef PVOID(__fastcall* PNvAPI_QueryInterface)(DWORD Code);
typedef NvAPI_Status(__cdecl* PNvAPI_EnumPhysicalGPUs)(HANDLE nvGPUHandle[NVAPI_MAX_PHYSICAL_GPUS], DWORD* pGpuCount);
typedef NvAPI_Status(__cdecl* PNvAPI_GPU_GetThermalSettings)(HANDLE hPhysicalGpu, DWORD sensorIndex, NV_GPU_THERMAL_SETTINGS* pThermalSettings);

typedef NvAPI_Status(__cdecl* PNvAPI_GPU_GetFullName)(HANDLE hPhysicalGpu, NvAPI_ShortString szName);
typedef NvAPI_Status(__cdecl* PNvAPI_Initialize)();
typedef NvAPI_Status(__cdecl* PNvAPI_GetErrorMessage)(NvAPI_Status nr, NvAPI_ShortString szDesc);
typedef NvAPI_Status(__cdecl* PNvAPI_GPU_GetTempIndex)(HANDLE hPhysicalGpu, NV_API_TEMP_INDEX* TempIndex);
typedef NvAPI_Status(__cdecl* PNvAPI_GPU_GetTemperatureEx)(HANDLE hPhysicalGpu, NV_API_ADV_TEMPERATURE* AdvTemp);


PNvAPI_EnumPhysicalGPUs NvAPI_EnumPhysicalGPUs;
PNvAPI_GPU_GetThermalSettings NvAPI_GPU_GetThermalSettings;
PNvAPI_GPU_GetFullName NvAPI_GPU_GetFullName;
PNvAPI_Initialize NvAPI_Initialize;
PNvAPI_GetErrorMessage NvAPI_GetErrorMessage;
PNvAPI_GPU_GetTempIndex NvAPI_GPU_GetTempIndex;
PNvAPI_GPU_GetTemperatureEx NvAPI_GPU_GetTemperatureEx;

HANDLE PhyGPUHandles[NVAPI_MAX_PHYSICAL_GPUS];
DWORD GpuCount = 0;
NvAPI_ShortString GPUNames[NVAPI_MAX_PHYSICAL_GPUS];
NvAPI_ShortString ErrorMsg;
#define MAKE_NVAPI_VERSION(typeName,ver) (DWORD)(sizeof(typeName) | ((ver) << 16))


//! Macro for constructing the version field of NV_GPU_THERMAL_SETTINGS_V2
#define NV_GPU_THERMAL_SETTINGS_VER_2   MAKE_NVAPI_VERSION(NV_GPU_THERMAL_SETTINGS,2)

//! Macro for constructing the version field of NV_GPU_THERMAL_SETTINGS
#define NV_GPU_THERMAL_SETTINGS_VER     NV_GPU_THERMAL_SETTINGS_VER_2

#define NV_GPU_TEMP_INDEX_VER MAKE_NVAPI_VERSION(NV_API_TEMP_INDEX , 2)
#define NV_GPU_ADV_TEMP_VER MAKE_NVAPI_VERSION(NV_API_ADV_TEMPERATURE , 2)


VOID ReadyForGPU()
{
    //Only support NV GPU for now

    NV_GPU_THERMAL_SETTINGS thermalSettings = { NV_GPU_THERMAL_SETTINGS_VER };

    hmodNvapi = LoadLibraryA("nvapi64.dll");
    PNvAPI_QueryInterface NvAPI_QueryInterface;

    if (hmodNvapi == 0)
    {
       // printf("no nvapi %u\n", GetLastError());
        return;
    }

    NvAPI_QueryInterface = (PNvAPI_QueryInterface)GetProcAddress(hmodNvapi, "nvapi_QueryInterface");

    if (NvAPI_QueryInterface == NULL)
    {
        //printf("unable to location nvapi_QueryInterface\n");
        FreeLibrary(hmodNvapi);
        hmodNvapi = 0;
        return;
    }

    NvAPI_Initialize = (PNvAPI_Initialize)NvAPI_QueryInterface(0x150E828UL);
    NvAPI_GPU_GetFullName = (PNvAPI_GPU_GetFullName)NvAPI_QueryInterface(0xCEEE8E9FUL);
    NvAPI_GPU_GetThermalSettings = (PNvAPI_GPU_GetThermalSettings)NvAPI_QueryInterface(0xE3640A56UL);
    NvAPI_EnumPhysicalGPUs = (PNvAPI_EnumPhysicalGPUs)NvAPI_QueryInterface(0xE5AC921FUL);
    NvAPI_GetErrorMessage = (PNvAPI_GetErrorMessage)NvAPI_QueryInterface(0x6C2D048CUL);
    NvAPI_GPU_GetTempIndex = (PNvAPI_GPU_GetTempIndex)NvAPI_QueryInterface(0xBC8163D);
    NvAPI_GPU_GetTemperatureEx = (PNvAPI_GPU_GetTemperatureEx)NvAPI_QueryInterface(0x65FE3AAD);

    if (NvAPI_Initialize == 0 || NvAPI_GPU_GetFullName == 0 || NvAPI_GPU_GetThermalSettings == 0 || NvAPI_EnumPhysicalGPUs == 0 || NvAPI_GetErrorMessage == 0)
    {
       // printf("unable to init basic nvapis\n");
        FreeLibrary(hmodNvapi);
        hmodNvapi = 0;
        return;
    }

    if (NvAPI_GPU_GetTempIndex == 0 || NvAPI_GPU_GetTemperatureEx == 0)
    {
       // printf("unable to init undocumented temperature nvapis\n");
        FreeLibrary(hmodNvapi);
        hmodNvapi = 0;
        return;
    }


    NvAPI_Status Status = NvAPI_Initialize();

    if (Status != NVAPI_OK)
    {
        NvAPI_GetErrorMessage(Status, ErrorMsg);
        //printf("Failed to init NVAPI, Reason: %s\n", ErrorMsg);
        FreeLibrary(hmodNvapi);
        hmodNvapi = 0;
        return;
    }

    Status = NvAPI_EnumPhysicalGPUs(PhyGPUHandles, &GpuCount);

    if (Status != NVAPI_OK)
    {
        NvAPI_GetErrorMessage(Status, ErrorMsg);
        //printf("Failed to enum physical GPUs, Reason: %s\n", ErrorMsg);
        FreeLibrary(hmodNvapi);
        hmodNvapi = 0;
        return;
    }

    DWORD n;

    for (n = 0; n < GpuCount; n++)
    {
        Status = NvAPI_GPU_GetFullName(PhyGPUHandles[n], GPUNames[n]);

        if (Status != NVAPI_OK)
        {
            NvAPI_GetErrorMessage(Status, ErrorMsg);
            //printf("Failed to get GPU full name for GPU%u, Reason: %s\n", n, ErrorMsg);
            FreeLibrary(hmodNvapi);
            hmodNvapi = 0;
            return;
        }
    }




    return;
}
int coreTemp;
int hotspotTemp;
int memoryTemp;


CHAR GPUName[100];
VOID UpdateGPUTemp()
{
    DWORD n;
    NvAPI_Status Status;
    NV_GPU_THERMAL_SETTINGS thermalSettings = { NV_GPU_THERMAL_SETTINGS_VER };
    DWORD n2;
    CHAR Msg[200];
    CHAR Number[50];
    NV_API_TEMP_INDEX TempIndex;
    NV_API_ADV_TEMPERATURE AdvTemp;

    //WCHAR ww[100];
    //swprintf_s(ww, 100, L"core:%u, hotspot:%u mem:%u\n", coreTemp, hotspotTemp, memoryTemp);
    //OutputDebugString(ww);

    if (hmodNvapi == 0)
    {
        return;
    }
    for (n = 0; n < GpuCount; n++)
    {
        Status = NvAPI_GPU_GetThermalSettings(PhyGPUHandles[n], NVAPI_THERMAL_TARGET_ALL, &thermalSettings);

        if (Status != NVAPI_OK)
        {
            NvAPI_GetErrorMessage(Status, ErrorMsg);
            printf("Failed to get GPU thermal settings for GPU%u, Reason: %s\n", n, ErrorMsg);
            return;
        }

        //strcpy_s(Msg, "GPU: ");
        //strcat_s(Msg, GPUNames[n]);
        //strcat_s(Msg, " ");
        strcpy_s(GPUName, 100, GPUNames[n]);

        for (n2 = 0; n2 < thermalSettings.count; n2++)
        {
            NV_THERMAL_TARGET target = thermalSettings.sensor[n2].target;

            if (target == 1)
            {
                coreTemp = thermalSettings.sensor[n2].currentTemp;
              //  sprintf_s(Number, "GPU Core: %u°C  ", thermalSettings.sensor[n2].currentTemp);
            }
            else if (target == 2)
            {
              //  memoryTemp = thermalSettings.sensor[n2].currentTemp;
               // sprintf_s(Number, "Memory: %u°C  ", thermalSettings.sensor[n2].currentTemp);
            }
            //else if (target == 4)
            //{
            //    sprintf_s(Number, "Power Supply: %u°C  ", thermalSettings.sensor[n2].currentTemp);
            //}
            //else if (target == 8)
            //{
            //    sprintf_s(Number, "Board: %u°C  ", thermalSettings.sensor[n2].currentTemp);
            //}
            //else
            //{
            //    sprintf_s(Number, "Unknown Part%u: %u°C  ", target, thermalSettings.sensor[n2].currentTemp);

            //}

          //  strcat_s(Msg, Number);
        }

        memset(&TempIndex, 0, sizeof(NV_API_TEMP_INDEX));
        memset(&AdvTemp, 0, sizeof(NV_API_ADV_TEMPERATURE));


        TempIndex.Version = NV_GPU_TEMP_INDEX_VER;

        Status = NvAPI_GPU_GetTempIndex(PhyGPUHandles[n], &TempIndex);

        if (Status != NVAPI_OK)
        {
            NvAPI_GetErrorMessage(Status, ErrorMsg);
         //   printf("Failed to get GPU temp index for GPU%u, Reason: %s\n", n, ErrorMsg);
        }
        else
        {
            if (TempIndex.GpuHotspotTempIndex >= 0x20 && TempIndex.MemoryTempIndex >= 0x20)
            {
               // printf("Index for GPU hotspot and memory both invalid for GPU %u\n", n);
            }
            else
            {

                AdvTemp.Version = NV_GPU_ADV_TEMP_VER;
                AdvTemp.QueryTempIndex = TempIndex.QueryTempIndex;

                Status = NvAPI_GPU_GetTemperatureEx(PhyGPUHandles[n], &AdvTemp);

                if (Status != NVAPI_OK)
                {
                    NvAPI_GetErrorMessage(Status, ErrorMsg);
                   // printf("Failed to get GPU advanced temperature for GPU%u, Reason: %s\n", n, ErrorMsg);
                }
                else
                {
                    if (TempIndex.GpuHotspotTempIndex < 0x20)
                    {
                        hotspotTemp = AdvTemp.TempTable[TempIndex.GpuHotspotTempIndex] / 256;
                        //sprintf_s(Number, "GPU Hotspot: %.0f°C  ", (float)AdvTemp.TempTable[TempIndex.GpuHotspotTempIndex] / 256);
                        //strcat_s(Msg, Number);
                    }

                    if (TempIndex.MemoryTempIndex < 0x20)
                    {
                        memoryTemp = AdvTemp.TempTable[TempIndex.MemoryTempIndex] / 256;
                        //sprintf_s(Number, "Memory: %.0f°C  ", (float)AdvTemp.TempTable[TempIndex.MemoryTempIndex] / 256);
                        //strcat_s(Msg, Number);
                    }
                }


            }


        }


    /*    strcat_s(Msg, "\n");

        printtobuffer(Msg);*/
    }
}



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGPUTmpGUIDlg 对话框



CGPUTmpGUIDlg::CGPUTmpGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPUTMPGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

}

// 析构函数
CGPUTmpGUIDlg::~CGPUTmpGUIDlg()
{
	GdiplusShutdown(gdiplusToken);
}
void CGPUTmpGUIDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGPUTmpGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
    ON_WM_CTLCOLOR()
    ON_WM_MOUSEMOVE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CGPUTmpGUIDlg 消息处理程序

BOOL CGPUTmpGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
    // 启用 WS_EX_COMPOSITED 样式
    ModifyStyleEx(0, WS_EX_COMPOSITED);

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
   // 初始化数据
    temperatureHistory.resize(20);


    ReadyForGPU();
    hoverInfo.Create(L"", WS_CHILD | SS_CENTER, CRect(0,0,120,60), this);
    hoverInfoBackgroundBrush.CreateSolidBrush(RGB(255, 255, 255));
        // 创建字体
    m_hoverInfoFont.CreatePointFont(90, _T("Arial"));

    // 设置字体到 hoverInfo 窗口
    hoverInfo.SetFont(&m_hoverInfoFont);
    hoverInfo.ShowWindow(SW_HIDE);

	SetTimer(1, 500, nullptr); // 每秒更新一次


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGPUTmpGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGPUTmpGUIDlg::OnPaint()
{
    {
        CPaintDC dc(this);



        CRect rect;
        GetDlgItem(IDC_GRAPH)->GetWindowRect(&rect);
        ScreenToClient(&rect);

        CDC memDC;
        memDC.CreateCompatibleDC(&dc);
        CBitmap bmp;
        bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
        CBitmap* pOldBmp = memDC.SelectObject(&bmp);

        Graphics graphics(memDC.GetSafeHdc());
        SolidBrush brush(Color(255, 0, 0, 0));
        graphics.FillRectangle(&brush, 0, 0, rect.Width(), rect.Height());

        Pen axisPen(Color(255, 0, 0, 0), 2);
        Pen gridPen(Color(100, 200, 200, 200)); // 半透明灰色网格线
        Pen corePen(Color(255, 255, 0, 0));
        Pen hotspotPen(Color(255, 0, 255, 0));
        Pen memoryPen(Color(255, 0, 0, 255));

        int leftMargin = 40;
        int bottomMargin = 40;
        int rightMargin = 10;
        int topMargin = 10;

        FontFamily fontFamily2(L"Arial");
        Gdiplus::Font font2(&fontFamily2, 18, FontStyleRegular, UnitPixel);
        SolidBrush brush2(Color(255, 255, 255, 255)); // 黑色

        // 确定文本位置
        int textX = rect.Width() - 260; // 根据文本宽度调整
        int textY = 10;

        // 绘制文本
        CStringW wText(GPUName);
        graphics.DrawString(wText, -1, &font2, PointF(textX, textY), &brush2);


        graphics.DrawLine(&axisPen, leftMargin, rect.Height() - bottomMargin, rect.Width() - rightMargin, rect.Height() - bottomMargin);
        graphics.DrawLine(&axisPen, leftMargin, rect.Height() - bottomMargin, leftMargin, topMargin);

        int graphHeight = rect.Height() - topMargin - bottomMargin;
        int graphWidth = rect.Width() - leftMargin - rightMargin;
        int pointSpacing = graphWidth / (temperatureHistory.size() - 1);

        // 绘制网格
        for (int i = 0; i <= 10; ++i) {
            int y = rect.Height() - bottomMargin - i * graphHeight / 10;
            graphics.DrawLine(&gridPen, leftMargin, y, rect.Width() - rightMargin, y);
        }
        for (int i = 0; i <= temperatureHistory.size() - 1; ++i) {
            int x = leftMargin + i * pointSpacing;
            graphics.DrawLine(&gridPen, x, rect.Height() - bottomMargin, x, topMargin);
        }

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 14, FontStyleRegular, UnitPixel);
        SolidBrush textBrush(Color(255, 255, 255, 255));

        for (size_t i = 0; i < temperatureHistory.size() - 1; ++i) {
            const auto& data1 = temperatureHistory[i];
            const auto& data2 = temperatureHistory[i + 1];

            graphics.DrawLine(&corePen,
                leftMargin + i * pointSpacing, rect.Height() - bottomMargin - (data1.coreTemp * graphHeight / 100),
                leftMargin + (i + 1) * pointSpacing, rect.Height() - bottomMargin - (data2.coreTemp * graphHeight / 100));

            graphics.DrawLine(&hotspotPen,
                leftMargin + i * pointSpacing, rect.Height() - bottomMargin - (data1.hotspotTemp * graphHeight / 100),
                leftMargin + (i + 1) * pointSpacing, rect.Height() - bottomMargin - (data2.hotspotTemp * graphHeight / 100));

            graphics.DrawLine(&memoryPen,
                leftMargin + i * pointSpacing, rect.Height() - bottomMargin - (data1.memoryTemp * graphHeight / 100),
                leftMargin + (i + 1) * pointSpacing, rect.Height() - bottomMargin - (data2.memoryTemp * graphHeight / 100));

            if (i % (temperatureHistory.size() / 5) == 0) {
                PointF timePoint(leftMargin + i * pointSpacing, rect.Height() - bottomMargin + 10);
                graphics.DrawString(data1.timeLabel, -1, &font, timePoint, &textBrush);
            }
        }

        for (int temp = 0; temp <= 100; temp += 20) {
            CString tempLabel;
            tempLabel.Format(L"%d", temp);
            PointF pointF(10, rect.Height() - bottomMargin - (temp * graphHeight / 100));
            graphics.DrawString(tempLabel, -1, &font, pointF, &textBrush);
        }

        dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

        memDC.SelectObject(pOldBmp);


    }

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);


	}
	else
	{
	
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGPUTmpGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CGPUTmpGUIDlg::UpdateTemperatureData()
{
    UpdateGPUTemp();

    TemperatureData newData;
    newData.coreTemp = coreTemp;
    newData.hotspotTemp = hotspotTemp;
    newData.memoryTemp = memoryTemp;

    SYSTEMTIME time;
    GetLocalTime(&time);
    newData.timeLabel.Format(L"%02d:%02d:%02d", time.wHour,time.wMinute, time.wSecond);

    temperatureHistory.push_back(newData);

    if (temperatureHistory.size() > 50) {
        temperatureHistory.erase(temperatureHistory.begin());
    }
}

void CGPUTmpGUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == 1) {
		// 更新数据逻辑
		// 调用 Invalidate() 以重绘窗口
		UpdateTemperatureData();
	}
	CRect rect;
	GetDlgItem(IDC_GRAPH)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect); // 只重绘指定区域

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CGPUTmpGUIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetSafeHwnd() == hoverInfo.GetSafeHwnd())
    {
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH)hoverInfoBackgroundBrush.GetSafeHandle();
    }

    return hbr;
}

int CGPUTmpGUIDlg::CalculateTemperature(CPoint point)
{
    CRect rect;
    CWnd* pGraph = GetDlgItem(IDC_GRAPH);
    if (pGraph != nullptr) {
        pGraph->GetClientRect(&rect);

        int topMargin = 10;
        int bottomMargin = 40;
        int graphHeight = rect.Height() - topMargin - bottomMargin;

        CClientDC dc(pGraph);
        int offset = 5;
        int foundY = -1;

        for (int dx = -offset; dx <= offset; ++dx) {
            for (int dy = -offset; dy <= offset; ++dy) {
                CPoint nearbyPoint(point.x + dx, point.y + dy);
                if (rect.PtInRect(nearbyPoint)) {
                    COLORREF color = dc.GetPixel(nearbyPoint);

                    if (color == RGB(255, 0, 0) || color == RGB(0, 255, 0) || color == RGB(0, 0, 255)) {
                        foundY = nearbyPoint.y;
                        break;
                    }
                }
            }
            if (foundY != -1) break;
        }

        if (foundY != -1) {
            int maxTemperature = 100;
            int minTemperature = 0;

            // 计算温度，考虑边距
            int adjustedY = foundY - topMargin;
            int temperature = ((graphHeight - adjustedY) * (maxTemperature - minTemperature)) / graphHeight + minTemperature;
            return temperature;
        }
    }
    return 0;

}

void CGPUTmpGUIDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect rect;
    GetDlgItem(IDC_GRAPH)->GetWindowRect(&rect);
    ScreenToClient(&rect);

    if (rect.PtInRect(point)) {
        CClientDC dc(this);
        int offset = 3; // 允许的误差范围
        CString info;

        for (int dx = -offset; dx <= offset; ++dx) {
            for (int dy = -offset; dy <= offset; ++dy) {
                CPoint nearbyPoint(point.x + dx, point.y + dy);
                if (rect.PtInRect(nearbyPoint)) {
                    COLORREF color = dc.GetPixel(nearbyPoint);

                    // 判断颜色
                    if (color == RGB(255, 0, 0)) { // 红色
                        int temperature = CalculateTemperature(point);
                        if (temperature)
                            info.Format(L"Core: %d°C", temperature+1);
                        break;
                    }
                    else if (color == RGB(0, 255, 0)) { // 绿色
                        int temperature = CalculateTemperature(point);
                        if (temperature)
                            info.Format(L"Hotspot: %d°C", temperature+1);
                        break;
                    }
                    else if (color == RGB(0, 0, 255)) { // 蓝色
                        int temperature = CalculateTemperature(point);
                        if (temperature)
                            info.Format(L"Memory: %d°C", temperature+1);
                        break;
                    }
                }
            }
            if (!info.IsEmpty()) break;
        }

        if (!info.IsEmpty()) {
          
            CRect graphRect;
            GetDlgItem(IDC_GRAPH)->GetClientRect(&graphRect);
          //  GetDlgItem(IDC_GRAPH)->ClientToScreen(&graphRect);

            // 计算 hoverInfo 的目标位置
            CRect hoverRect(point.x + 10, point.y - 40, point.x + 100, point.y - 30);

            // 检查 hoverInfo 是否在图表范围内
            if (graphRect.PtInRect(hoverRect.TopLeft()) && graphRect.PtInRect(hoverRect.BottomRight())) 
            {
              

                hoverInfo.SetWindowText(info);
                hoverInfo.MoveWindow(point.x + 10, point.y - 40, 100, 15);

                hoverInfo.ShowWindow(SW_SHOW);
            }
        }
        else {
            hoverInfo.ShowWindow(SW_HIDE);
           
        }
    }
    else {
        hoverInfo.ShowWindow(SW_HIDE);
    }

    CDialogEx::OnMouseMove(nFlags, point);
}



BOOL CGPUTmpGUIDlg::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    return TRUE;
}
