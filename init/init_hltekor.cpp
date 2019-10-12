/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2019, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::init::property_set;


void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[],
        char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties() {

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("N900K") == 0) {
        /* hltektt - KT Corp (formerly Korea Telecom) */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/hltektt/hltektt:5.0/LRX21V/N900KKKU0GOC4:user/release-keys");
        property_override("ro.build.description", "hltektt-user 5.0 LRX21V N900KKKU0GOC4 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N900K");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "hltektt");
    } else if (bootloader.find("N900L") == 0) {
        /* hltelgt - LG Uplus */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/hltelgt/hltelgt:5.0/LRX21V/N900LKLU0GPI1:user/release-keys");
        property_override("ro.build.description", "hltelgt-user 5.0 LRX21V N900LKLU0GPI1 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N900L");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "hltelgt");
    } else if (bootloader.find("N900S") == 0) {
        /* hlteskt - SK Telecom */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/hlteskt/hlteskt:5.0/LRX21V/N900SKSU0GPI1:user/release-keys");
        property_override("ro.build.description", "hlteskt-user 5.0 LRX21V N900SKSU0GPI1 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N900S");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "hlteskt");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}
