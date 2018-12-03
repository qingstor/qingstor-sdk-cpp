// +-------------------------------------------------------------------------
// | Copyright (C) 2017 Yunify, Inc.
// +-------------------------------------------------------------------------
// | Licensed under the Apache License, Version 2.0 (the "License");
// | you may not use this work except in compliance with the License.
// | You may obtain a copy of the License in the LICENSE file, or at:
// |
// | http://www.apache.org/licenses/LICENSE-2.0
// |
// | Unless required by applicable law or agreed to in writing, software
// | distributed under the License is distributed on an "AS IS" BASIS,
// | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// | See the License for the specific language governing permissions and
// | limitations under the License.
// +-------------------------------------------------------------------------

#pragma once

#include "../QsBaseType.h"
#include <string>

// Headers of CustomizedType.
#include "CloudfuncArgsType.h"

#ifdef BUILD_C_STYLE_INTERFACE
#include "../service_with_c_style/types/NotificationType.h"
#endif							// BUILD_C_STYLE_INTERFACE

// Event processing service'flag
// Cloudfunc's available values: tupu-porn, notifier, image
#define SETTING_NOTIFICATION_CLOUDFUNC_FLAG 0x1

#define SETTING_NOTIFICATION_CLOUDFUNC_ARGS_FLAG 0x2

// event types'flag
#define SETTING_NOTIFICATION_EVENT_TYPES_FLAG 0x4

// notification id'flag
#define SETTING_NOTIFICATION_ID_FLAG 0x8

// notify url'flag
#define SETTING_NOTIFICATION_NOTIFY_URL_FLAG 0x10

// Object name matching rule'flag
#define SETTING_NOTIFICATION_OBJECT_FILTERS_FLAG 0x20

//NotificationType presents costom type：Notification.
class QS_SDK_API NotificationType:QsBaseType
{

public:
    NotificationType()
    {
    };
    NotificationType(std::string serializedStr);

#ifdef BUILD_C_STYLE_INTERFACE
    NotificationType(qs_notification_t notification);
    qs_notification_t *toCStyleObj();
#endif							// BUILD_C_STYLE_INTERFACE// Event processing service
    // Cloudfunc's available values: tupu-porn, notifier, image

    inline void SetCloudfunc(std::string Cloudfunc)
    {
        m_settingFlag |= SETTING_NOTIFICATION_CLOUDFUNC_FLAG;
        m_Cloudfunc = Cloudfunc;
    };

    inline std::string GetCloudfunc()
    {
        return m_Cloudfunc;
    };

    inline void SetCloudfuncArgs(CloudfuncArgsType CloudfuncArgs)
    {
        m_settingFlag |= SETTING_NOTIFICATION_CLOUDFUNC_ARGS_FLAG;
        m_CloudfuncArgs = CloudfuncArgs;
    };

    inline CloudfuncArgsType GetCloudfuncArgs()
    {
        return m_CloudfuncArgs;
    };

    // event types
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetEventTypes(qs_list_t * event_types)
    {
        m_settingFlag |= SETTING_NOTIFICATION_EVENT_TYPES_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, event_types)
        {
            m_EventTypes.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetEventTypes(std::vector < std::string > EventTypes)
    {
        m_settingFlag |= SETTING_NOTIFICATION_EVENT_TYPES_FLAG;
        m_EventTypes = EventTypes;
    };

    inline std::vector < std::string > GetEventTypes()
    {
        return m_EventTypes;
    };

    // notification id

    inline void SetID(std::string ID)
    {
        m_settingFlag |= SETTING_NOTIFICATION_ID_FLAG;
        m_ID = ID;
    };

    inline std::string GetID()
    {
        return m_ID;
    };

    // notify url

    inline void SetNotifyURL(std::string NotifyURL)
    {
        m_settingFlag |= SETTING_NOTIFICATION_NOTIFY_URL_FLAG;
        m_NotifyURL = NotifyURL;
    };

    inline std::string GetNotifyURL()
    {
        return m_NotifyURL;
    };

    // Object name matching rule
#ifdef BUILD_C_STYLE_INTERFACE
    inline void SetObjectFilters(qs_list_t * object_filters)
    {
        m_settingFlag |= SETTING_NOTIFICATION_OBJECT_FILTERS_FLAG;
        qs_string_item_t *item;
        qs_list_for_each_entry(qs_string_item_t, item, object_filters)
        {
            m_ObjectFilters.push_back(item->content);
        }
    };
#endif							// BUILD_C_STYLE_INTERFACE

    inline void SetObjectFilters(std::vector < std::string > ObjectFilters)
    {
        m_settingFlag |= SETTING_NOTIFICATION_OBJECT_FILTERS_FLAG;
        m_ObjectFilters = ObjectFilters;
    };

    inline std::vector < std::string > GetObjectFilters()
    {
        return m_ObjectFilters;
    };

    std::string Serialize();

private:

    // Event processing service
    // Cloudfunc's available values: tupu-porn, notifier, image
    std::string m_Cloudfunc;	// Required

    CloudfuncArgsType m_CloudfuncArgs;

    // event types

    std::vector < std::string > m_EventTypes;	// Required

    // notification id
    std::string m_ID;			// Required

    // notify url
    std::string m_NotifyURL;

    // Object name matching rule

    std::vector < std::string > m_ObjectFilters;

    int setting_flag;
};
