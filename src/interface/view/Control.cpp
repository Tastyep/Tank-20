#include "interface/view/Control.hpp"
#include "Utility.hpp"
#include "domain/Action.hpp"
#include "interface/Keyboard.hpp"
#include "interface/service/ControllerMapper.hpp"

#include <imgui.h>

#include <iostream>
#include <memory>
#include <utility>

namespace Interface::View {

Control::Control(std::shared_ptr<Service::ControllerMapper> controllerMapper)
    : _controllerMapper(std::move(controllerMapper)) {
  _refreshKeyBuffers();
}

void Control::render(sf::RenderWindow & /* window */) {
  // Draw popup window
  bool       show = true;
  const auto popupFlags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;

  ImGui::Begin("Control", &show, popupFlags);
  for (size_t i = 0; i < static_cast<size_t>(Domain::ActionCode::Count); ++i) {

    auto charCapture = [this, i](ImGuiInputTextCallbackData *data) {
      if (data->EventFlag == ImGuiInputTextFlags_CallbackAlways) {
        ImGuiIO &io = ImGui::GetIO();
        for (int j = 0; j < IM_ARRAYSIZE(io.KeysDown); ++j) {
          if (io.KeysDown[j]) {
            const auto key = Keyboard::KeyCode{j};
            const auto action = Domain::ActionCode{static_cast<int>(i)};
            _controllerMapper->map(key, action);
            this->_refreshKeyBuffers();

            const auto keyName = Keyboard::keyName(key);
            data->Buf = _keyBuffers[i].data();
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, keyName.data());
          }
        }
      }
      return 0;
    };
    using ReplacementLambdaType = decltype(charCapture);

    ImGui::InputText(
        Domain::actionName(Domain::ActionCode{static_cast<int>(i)}).data(),
        _keyBuffers[i].data(), _keyBuffers[i].capacity() + 1,
        ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CallbackAlways,
        [](ImGuiInputTextCallbackData *data) {
          auto handler = *static_cast<ReplacementLambdaType *>(data->UserData);
          return handler(data);
        },
        &charCapture);
  }
  ImGui::End();
}

void Control::_refreshKeyBuffers() {
  for (size_t i = 0; i < static_cast<size_t>(Domain::ActionCode::Count); ++i) {
    auto key = (*_controllerMapper)[Domain::ActionCode{static_cast<int>(i)}];

    if (key) {
      _keyBuffers[i] = Keyboard::keyName(*key);
    } else {
      _keyBuffers[i].clear();
    }
  }
}

} // namespace Interface::View
