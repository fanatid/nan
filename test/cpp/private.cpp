/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2016 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

using namespace Nan;  // NOLINT(build/namespaces)

NAN_METHOD(HasPrivateYes) {
  HandleScope scope;
  v8::Local<v8::Object> object = New<v8::Object>();
  v8::Local<v8::String> key = New("key").ToLocalChecked();
  v8::Local<v8::String> value = New("value").ToLocalChecked();
  Maybe<bool> mb = SetPrivate(object, key, value);
  bool v1 = mb.IsJust() ? mb.FromJust() : false;
  mb = HasPrivate(object, key);
  bool v2 = mb.IsJust() ? mb.FromJust() : false;
  MaybeLocal<v8::Value> mv = GetPrivate(object, key);
  bool v3 = mv.IsEmpty() ? false :
      !strcmp(*Utf8String(mv.ToLocalChecked()), "value");
  info.GetReturnValue().Set(v1 && v2 && v3);
}

NAN_METHOD(HasPrivateNo) {
  HandleScope scope;
  v8::Local<v8::Object> object = New<v8::Object>();
  Maybe<bool> mb = HasPrivate(object, New("key").ToLocalChecked());
  bool v1 = mb.IsJust() ? !mb.FromJust() : false;
  MaybeLocal<v8::Value> q = GetPrivate(object, New("key").ToLocalChecked());
  bool v2 = !q.IsEmpty() ? q.ToLocalChecked()->IsUndefined() : false;
  info.GetReturnValue().Set(v1 && v2);
}

NAN_METHOD(DeletePrivateNo) {
  HandleScope scope;
  v8::Local<v8::Object> object = New<v8::Object>();
  v8::Local<v8::String> key = New("key").ToLocalChecked();
  v8::Local<v8::String> value = New("value").ToLocalChecked();
  Maybe<bool> mb = DeletePrivate(object, key);
  bool v1 = mb.IsJust() ? mb.FromJust() : false;
  mb = SetPrivate(object, key, value);
  bool v2 = mb.IsJust() ? mb.FromJust() : false;
  mb = DeletePrivate(object, key);
  bool v3 = mb.IsJust() ? mb.FromJust() : false;
  info.GetReturnValue().Set(v1 && v2 && v3);
}

NAN_MODULE_INIT(Init) {
  Set(target
    , New<v8::String>("hasPrivateYes").ToLocalChecked()
    , GetFunction(New<v8::FunctionTemplate>(HasPrivateYes)).ToLocalChecked()
  );
  Set(target
    , New<v8::String>("hasPrivateNo").ToLocalChecked()
    , GetFunction(New<v8::FunctionTemplate>(HasPrivateNo)).ToLocalChecked()
  );
  Set(target
    , New<v8::String>("deletePrivateNo").ToLocalChecked()
    , GetFunction(New<v8::FunctionTemplate>(DeletePrivateNo)).ToLocalChecked()
  );
}

NODE_MODULE(private, Init)
