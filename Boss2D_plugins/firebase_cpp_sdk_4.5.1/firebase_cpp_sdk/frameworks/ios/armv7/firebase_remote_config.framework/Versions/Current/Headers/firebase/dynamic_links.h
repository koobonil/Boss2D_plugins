// Copyright 2017 Google Inc. All Rights Reserved.

#ifndef FIREBASE_DYNAMIC_LINKS_CLIENT_CPP_SRC_INCLUDE_FIREBASE_DYNAMIC_LINKS_H_
#define FIREBASE_DYNAMIC_LINKS_CLIENT_CPP_SRC_INCLUDE_FIREBASE_DYNAMIC_LINKS_H_

#include <string>

#include "firebase/app.h"
#include "firebase/internal/common.h"

#if !defined(DOXYGEN) && !defined(SWIG)
FIREBASE_APP_REGISTER_CALLBACKS_REFERENCE(dynamic_links)
#endif  // !defined(DOXYGEN) && !defined(SWIG)

namespace firebase {

/// @brief Firebase Dynamic Links API.
///
/// Firebase Dynamic Links is a cross-platform solution for generating and
/// receiving links, whether or not the app is already installed.
namespace dynamic_links {

/// @brief Error code used by Futures returned by this API.
enum ErrorCode {
  kErrorCodeSuccess = 0,
  kErrorCodeFailed,
};

/// @brief The received Dynamic Link.
struct DynamicLink {
  /// The URL that was passed to the app.
  std::string url;
};

/// @brief Base class used to receive Dynamic Links.
class Listener {
 public:
  virtual ~Listener();

  /// Called on the client when a dynamic link arrives.
  ///
  /// @param[in] dynamic_link The data describing the Dynamic Link.
  virtual void OnDynamicLinkReceived(const DynamicLink* dynamic_link) = 0;
};

/// @brief Initialize Firebase Dynamic Links.
///
/// After Initialize is called, the implementation may call functions on the
/// Listener provided at any time.
///
/// @param[in] app The Firebase App object for this application.
/// @param[in] listener A Listener object that recieves Dynamic Links.
///
/// @return kInitResultSuccess if initialization succeeded, or
/// kInitResultFailedMissingDependency on Android if Google Play services is
/// not available on the current device.
InitResult Initialize(const App& app, Listener* listener);

/// @brief Terminate Firebase Dynamic Links.
void Terminate();

/// @brief Set the listener for receiving Dynamic Links.
///
/// @param[in] listener A Listener object that receives Dynamic Links.
///
/// @return Pointer to the previously set listener.
Listener* SetListener(Listener* listener);

/// Fetch any pending dynamic links. Each pending link will trigger a call to
/// the registered Listener class.
///
/// This function is implicitly called on initialization. On iOS this is called
/// automatically when the app gains focus, but on Android this needs to be
/// called manually.
void Fetch();

}  // namespace dynamic_links
}  // namespace firebase

#endif  // FIREBASE_DYNAMIC_LINKS_CLIENT_CPP_SRC_INCLUDE_FIREBASE_DYNAMIC_LINKS_H_
