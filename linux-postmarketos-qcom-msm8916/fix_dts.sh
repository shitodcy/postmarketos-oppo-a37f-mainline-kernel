sed -i '/pinctrl-0 = <&blsp_uart2_console_default>;/d' arch/arm64/boot/dts/qcom/msm8916-oppo-a37.dts
sed -i '/pinctrl-1 = <&blsp_uart2_console_sleep>;/d' arch/arm64/boot/dts/qcom/msm8916-oppo-a37.dts
sed -i '/pinctrl-names = "default", "sleep";/d' arch/arm64/boot/dts/qcom/msm8916-oppo-a37.dts
