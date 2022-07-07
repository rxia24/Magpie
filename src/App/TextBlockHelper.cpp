﻿#include "pch.h"
#include "TextBlockHelper.h"
#if __has_include("TextBlockHelper.g.cpp")
#include "TextBlockHelper.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml::Controls;


namespace winrt::Magpie::App::implementation {

DependencyProperty TextBlockHelper::_isAutoTooltipProperty = DependencyProperty::RegisterAttached(
    L"IsAutoTooltip",
    xaml_typename<bool>(),
    xaml_typename<Magpie::App::TextBlockHelper>(),
    PropertyMetadata(box_value(false), _OnIsAutoTooltipChanged)
);

void TextBlockHelper::_OnIsAutoTooltipChanged(DependencyObject const& sender, DependencyPropertyChangedEventArgs const& args) {
    TextBlock tb = sender.as<TextBlock>();

    bool newValue = args.NewValue().as<bool>();
    _SetTooltipBasedOnTrimmingState(tb, newValue);

    if (newValue) {
        tb.SizeChanged(_TextBlock_SizeChanged);
    } else {
        // 不支持取消
        assert(false);
    }
}

void TextBlockHelper::_TextBlock_SizeChanged(IInspectable const& sender, SizeChangedEventArgs const&) {
    _SetTooltipBasedOnTrimmingState(sender.as<TextBlock>(), true);
}

void TextBlockHelper::_SetTooltipBasedOnTrimmingState(const TextBlock& tb, bool isAttached) {
    ToolTipService::SetToolTip(tb, isAttached && tb.IsTextTrimmed() ? box_value(tb.Text()) : nullptr);
}

}
