#include "system/reboot_reason.h"
#include "memfault/ports/reboot_reason.h"

// FIXME: Rather than switching over all of Pebble's reboot tracking to memfault
// today, let's perform a translation from Pebble's tracking to Memfault's.

static eMemfaultRebootReason prv_pbl_reboot_to_mflt_reboot(RebootReasonCode reason) {
  switch (reason) {
    case RebootReasonCode_Unknown:
      return kMfltRebootReason_Unknown;
    case RebootReasonCode_LowBattery:
      return kMfltRebootReason_LowPower;
    case RebootReasonCode_SoftwareUpdate:
      return kMfltRebootReason_FirmwareUpdate;
    case RebootReasonCode_ResetButtonsHeld:
      return kMfltRebootReason_ButtonReset;
    case RebootReasonCode_ShutdownMenuItem:
      return kMfltRebootReason_UserShutdown;

    // [MJ] TODO: Custom reboot reasons here.
    case RebootReasonCode_FactoryResetShutdown:
    case RebootReasonCode_MfgShutdown:
    case RebootReasonCode_Serial:
    case RebootReasonCode_RemoteReset:
    case RebootReasonCode_PrfReset:
    case RebootReasonCode_ForcedCoreDump:
    case RebootReasonCode_PrfIdle:
    case RebootReasonCode_PrfResetButtonsHeld:
      return kMfltRebootReason_Unknown;

    case RebootReasonCode_Watchdog:
      return kMfltRebootReason_SoftwareWatchdog;
    case RebootReasonCode_Assert:
      return kMfltRebootReason_Assert;
    case RebootReasonCode_StackOverflow:
      return kMfltRebootReason_StackOverflow;
    case RebootReasonCode_HardFault:
      return kMfltRebootReason_HardFault;

    // [MJ] TODO: Custom reboot reasons here.
    case RebootReasonCode_LauncherPanic:
    case RebootReasonCode_ClockFailure: // Not used on 3.x
    case RebootReasonCode_AppHardFault: // Not used on 3.x
    case RebootReasonCode_EventQueueFull:
    case RebootReasonCode_WorkerHardFault: // Off by default, compile in with WORKER_CRASH_CAUSES_RESET
      return kMfltRebootReason_Unknown;

    case RebootReasonCode_OutOfMemory:
      return kMfltRebootReason_OutOfMemory;

    // [MJ] TODO: Custom reboot reasons here.
    case RebootReasonCode_FactoryResetReset:
    case RebootReasonCode_DialogBootFault:
    case RebootReasonCode_BtCoredump:
    case RebootReasonCode_CoreDump:  // Core dump initiated without a more specific reason set
    case RebootReasonCode_CoreDumpEntryFailed:
      return kMfltRebootReason_Unknown;
  }

  return kMfltRebootReason_Unknown;
}

void memfault_reboot_reason_get(sResetBootupInfo *reset_info) {
  RebootReasonCode pbl_reason = reboot_reason_get_last_reboot_reason();  // Should this be reboot_reason_get()?
  reset_info->reset_reason = prv_pbl_reboot_to_mflt_reboot(pbl_reason);
}
