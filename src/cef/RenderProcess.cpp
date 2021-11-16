#include "RenderProcess.hpp"

static CefRefPtr<CefValue> CefV8ValueToCefValue(const CefRefPtr<CefV8Value> &valueV8) {
    CefRefPtr<CefValue> value = CefValue::Create();

    if (!valueV8->IsValid())
        return value;

    if (valueV8->IsBool()) {
        value->SetBool(valueV8->GetBoolValue());
        return value;
    }

    if (valueV8->IsInt()) {
        value->SetInt(valueV8->GetIntValue());
        return value;
    }

    if (valueV8->IsDouble()) {
        value->SetDouble(valueV8->GetDoubleValue());
        return value;
    }

    if (valueV8->IsString()) {
        value->SetString(valueV8->GetStringValue());
        return value;
    }

    if (valueV8->IsArray()) {
        CefRefPtr<CefListValue> list = CefListValue::Create();

        for (int i = 0; i < valueV8->GetArrayLength(); i++) {
            CefRefPtr<CefV8Value> indexValue = valueV8->GetValue(i);

            // Prevent looping on circular structure
            if (indexValue->IsSame(valueV8))
                continue;

            list->SetValue(i, CefV8ValueToCefValue(indexValue));
        }

        value->SetList(list);
        return value;
    }

    if (valueV8->IsObject()) {
        std::vector<CefString> keys;
        CefRefPtr<CefDictionaryValue> dictionary = CefDictionaryValue::Create();

        if (valueV8->GetKeys(keys)) {
            for (const CefString &key : keys) {
                CefRefPtr<CefV8Value> keyValue = valueV8->GetValue(key);

                // Prevent looping on circular structure
                if (keyValue->IsSame(valueV8))
                    continue;

                dictionary->SetValue(key, CefV8ValueToCefValue(keyValue));
            }
        }

        value->SetDictionary(dictionary);
        return value;
    }

    value->SetNull();
    return value;
}

void RenderProcess::OnContextCreated(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> global = context->GetGlobal();
    CefRefPtr<CefV8Value> engine = CefV8Value::CreateObject(nullptr, nullptr);

    CefRefPtr<CefV8Value> emitter = CefV8Value::CreateFunction("Emit", this);
    engine->SetValue(emitter->GetFunctionName(), emitter, V8_PROPERTY_ATTRIBUTE_READONLY);

    global->SetValue("Engine", engine, V8_PROPERTY_ATTRIBUTE_READONLY);
}

bool RenderProcess::Execute(
        const CefString &name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList &arguments,
        CefRefPtr<CefV8Value> &retval,
        CefString &exception) {
    if (name == "Emit") {
        if (arguments.empty() || !arguments[0]->IsString())
            return false;

        CefRefPtr<CefProcessMessage> message = CefProcessMessage::
                Create(arguments[0]->GetStringValue());

        CefRefPtr<CefListValue> args = message->GetArgumentList();
        for (int i = 1; i < arguments.size(); i++)
            args->SetValue(i - 1, CefV8ValueToCefValue(arguments[i]));

        CefRefPtr<CefFrame> frame = CefV8Context::GetCurrentContext()->GetFrame();
        frame->SendProcessMessage(PID_BROWSER, message);

        return true;
    }

    return false;
}
