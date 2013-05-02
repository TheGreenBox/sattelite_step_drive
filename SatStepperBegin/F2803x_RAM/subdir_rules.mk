################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DSP2803x_GlobalVariableDefs.obj: /home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/home/akindyakov/source/step_course/development_kits/~SupportFiles/F2803x_headers" --include_path="/home/akindyakov/source/step_course/libs/app_libs/motor_control/drivers/f2803x_v1.1" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/include" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_common/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="DSP2803x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

control_algo.obj: ../control_algo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/home/akindyakov/source/step_course/development_kits/~SupportFiles/F2803x_headers" --include_path="/home/akindyakov/source/step_course/libs/app_libs/motor_control/drivers/f2803x_v1.1" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/include" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_common/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="control_algo.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

init.obj: ../init.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/home/akindyakov/source/step_course/development_kits/~SupportFiles/F2803x_headers" --include_path="/home/akindyakov/source/step_course/libs/app_libs/motor_control/drivers/f2803x_v1.1" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/include" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_common/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="init.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/home/akindyakov/source/step_course/development_kits/~SupportFiles/F2803x_headers" --include_path="/home/akindyakov/source/step_course/libs/app_libs/motor_control/drivers/f2803x_v1.1" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/include" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_common/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pwm_wrap_module.obj: ../pwm_wrap_module.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/home/akindyakov/source/step_course/development_kits/~SupportFiles/F2803x_headers" --include_path="/home/akindyakov/source/step_course/libs/app_libs/motor_control/drivers/f2803x_v1.1" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/include" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_common/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="pwm_wrap_module.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

state.obj: ../state.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --include_path="/opt/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/home/akindyakov/source/step_course/development_kits/~SupportFiles/F2803x_headers" --include_path="/home/akindyakov/source/step_course/libs/app_libs/motor_control/drivers/f2803x_v1.1" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_headers/include" --include_path="/home/akindyakov/source/step_course/device_support/f2803x/v122/DSP2803x_common/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="state.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


