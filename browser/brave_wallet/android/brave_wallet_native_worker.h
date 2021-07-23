/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_BRAVE_WALLET_ANDROID_BRAVE_WALLET_NATIVE_WORKER_H_
#define BRAVE_BROWSER_BRAVE_WALLET_ANDROID_BRAVE_WALLET_NATIVE_WORKER_H_

#include <jni.h>
#include <string>
#include <utility>
#include <vector>

#include "base/android/jni_weak_ref.h"
#include "base/memory/weak_ptr.h"
#include "brave/components/brave_wallet/common/brave_wallet.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace chrome {
namespace android {
class BraveWalletNativeWorker {
 public:
  BraveWalletNativeWorker(JNIEnv* env,
                          const base::android::JavaRef<jobject>& obj);
  ~BraveWalletNativeWorker();

  void Destroy(JNIEnv* env,
               const base::android::JavaParamRef<jobject>& jcaller);
  base::android::ScopedJavaLocalRef<jstring> GetRecoveryWords(JNIEnv* env);
  bool IsWalletLocked(JNIEnv* env);
  base::android::ScopedJavaLocalRef<jstring> CreateWallet(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& password);
  void LockWallet(JNIEnv* env);
  bool UnlockWallet(JNIEnv* env,
                    const base::android::JavaParamRef<jstring>& password);
  base::android::ScopedJavaLocalRef<jstring> RestoreWallet(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& mnemonic,
      const base::android::JavaParamRef<jstring>& password);
  void ResetWallet(JNIEnv* env);

  void GetAssetPrice(
      JNIEnv* env,
      const base::android::JavaParamRef<jobjectArray>& from_assets,
      const base::android::JavaParamRef<jobjectArray>& to_assets);
  void OnGetPrice(bool success,
                  std::vector<brave_wallet::mojom::AssetPricePtr> prices);

  void GetAssetPriceHistory(JNIEnv* env,
                            const base::android::JavaParamRef<jstring>& asset,
                            const jint timeFrameType);
  void OnGetPriceHistory(
      bool success,
      std::vector<brave_wallet::mojom::AssetTimePricePtr> values);

 private:
  void EnsureConnected();
  void OnConnectionError();

  mojo::Remote<brave_wallet::mojom::KeyringController> keyring_controller_;
  mojo::Remote<brave_wallet::mojom::AssetRatioController>
      asset_ratio_controller_;

  JavaObjectWeakGlobalRef weak_java_brave_wallet_native_worker_;
  base::WeakPtrFactory<BraveWalletNativeWorker> weak_ptr_factory_;
};
}  // namespace android
}  // namespace chrome

#endif  // BRAVE_BROWSER_BRAVE_WALLET_ANDROID_BRAVE_WALLET_NATIVE_WORKER_H_
