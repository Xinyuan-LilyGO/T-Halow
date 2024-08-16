##
## Auto Generated makefile by CDK
## Do not modify this file, and any manual changes will be erased!!!   
##
## BuildSet
ProjectName            :=txw4002a
ConfigurationName      :=BuildSet
WorkspacePath          :=./
ProjectPath            :=./
IntermediateDirectory  :=Obj
OutDir                 :=$(IntermediateDirectory)
User                   :=29076
Date                   :=16/08/2024
CDKPath                :=../../../Users/29076/AppData/Roaming/C-Sky/CDK/
LinkerName             :=csky-elfabiv2-gcc
LinkerNameoption       :=
SIZE                   :=csky-elfabiv2-size
READELF                :=csky-elfabiv2-readelf
CHECKSUM               :=crc32
SharedObjectLinkerName :=
ObjectSuffix           :=.o
DependSuffix           :=.d
PreprocessSuffix       :=.i
DisassemSuffix         :=.asm
IHexSuffix             :=.ihex
BinSuffix              :=.bin
ExeSuffix              :=.elf
LibSuffix              :=.a
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
ElfInfoSwitch          :=-hlS
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
UnPreprocessorSwitch   :=-U
SourceSwitch           :=-c 
ObjdumpSwitch          :=-S
ObjcopySwitch          :=-O ihex
ObjcopyBinSwitch       :=-O binary
OutputFile             :=$(ProjectName)
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=txw4002a.txt
MakeDirCommand         :=mkdir
LinkOptions            := -mcpu=ck803  -nostartfiles -Wl,--gc-sections -T"$(ProjectPath)/utilities/gcc_csky.ld"
LinkOtherFlagsOption   :=-Wl,-zmax-page-size=1024
IncludePackagePath     :=
IncludeCPath           := $(IncludeSwitch). $(IncludeSwitch)../csky/configs $(IncludeSwitch)../csky/csi_core/include $(IncludeSwitch)../csky/csi_driver/include $(IncludeSwitch)../csky/csi_kernel/include $(IncludeSwitch)../csky/csi_kernel/rhino/arch/include $(IncludeSwitch)../csky/csi_kernel/rhino/common $(IncludeSwitch)../csky/csi_kernel/rhino/core/include $(IncludeSwitch)../csky/csi_kernel/rhino/driver $(IncludeSwitch)../csky/csi_kernel/rhino/pwrmgmt $(IncludeSwitch)../csky/libs/include $(IncludeSwitch)../sdk/include $(IncludeSwitch)../sdk/include/chip $(IncludeSwitch)../sdk/include/chip/txw4002ack803 $(IncludeSwitch)../sdk/include/lib $(IncludeSwitch)../test  
IncludeAPath           := $(IncludeSwitch). $(IncludeSwitch)../csky/configs $(IncludeSwitch)../csky/csi_core/include $(IncludeSwitch)../csky/csi_driver/include $(IncludeSwitch)../csky/csi_kernel/include $(IncludeSwitch)../csky/csi_kernel/rhino/arch/include $(IncludeSwitch)../csky/csi_kernel/rhino/common $(IncludeSwitch)../csky/csi_kernel/rhino/core/include $(IncludeSwitch)../csky/csi_kernel/rhino/driver $(IncludeSwitch)../csky/csi_kernel/rhino/pwrmgmt $(IncludeSwitch)../csky/libs/include $(IncludeSwitch)../sdk/include $(IncludeSwitch)../sdk/include/chip $(IncludeSwitch)../sdk/include/chip/txw4002ack803 $(IncludeSwitch)../sdk/include/lib $(IncludeSwitch)../test  
Libs                   := -Wl,--whole-archive  -Wl,--no-whole-archive $(LibrarySwitch)m  
ArLibs                 := "m" 
PackagesLibPath        :=
LibPath                := $(PackagesLibPath) 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       :=csky-elfabiv2-ar rcu
CXX      :=csky-elfabiv2-g++
CC       :=csky-elfabiv2-gcc
AS       :=csky-elfabiv2-gcc
OBJDUMP  :=csky-elfabiv2-objdump
OBJCOPY  :=csky-elfabiv2-objcopy
CXXFLAGS := -mcpu=ck803   $(PreprocessorSwitch)__NO_BOARD_INIT  $(PreprocessorSwitch)TXW4002ACK803  $(PreprocessorSwitch)SKB_POOL_ENABLE  $(PreprocessorSwitch)MPOOL_ALLOC   -Os  -g  -Wall -ffunction-sections -fdata-sections -Wno-comment -Wno-unused-function -Wno-unused-but-set-variable 
CFLAGS   := -mcpu=ck803   $(PreprocessorSwitch)__NO_BOARD_INIT  $(PreprocessorSwitch)TXW4002ACK803  $(PreprocessorSwitch)SKB_POOL_ENABLE  $(PreprocessorSwitch)MPOOL_ALLOC   -Os  -g  -Wall -ffunction-sections -fdata-sections -Wno-comment -Wno-unused-function -Wno-unused-but-set-variable 
ASFLAGS  := -mcpu=ck803   $(PreprocessorSwitch)__NO_BOARD_INIT  $(PreprocessorSwitch)TXW4002ACK803   -Wa,--gdwarf2    


Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/device$(ObjectSuffix) $(IntermediateDirectory)/hgic_usart$(ObjectSuffix) $(IntermediateDirectory)/hgic_malloc$(ObjectSuffix) $(IntermediateDirectory)/hgic_assert$(ObjectSuffix) $(IntermediateDirectory)/libc_malloc$(ObjectSuffix) $(IntermediateDirectory)/libc_minilibc_port$(ObjectSuffix) $(IntermediateDirectory)/mm_dq_addlast$(ObjectSuffix) $(IntermediateDirectory)/mm_dq_rem$(ObjectSuffix) $(IntermediateDirectory)/mm_lib_mallinfo$(ObjectSuffix) \
	$(IntermediateDirectory)/mm_mm_addfreechunk$(ObjectSuffix) $(IntermediateDirectory)/mm_mm_free$(ObjectSuffix) $(IntermediateDirectory)/mm_mm_initialize$(ObjectSuffix) $(IntermediateDirectory)/mm_mm_leak$(ObjectSuffix) $(IntermediateDirectory)/mm_mm_mallinfo$(ObjectSuffix) $(IntermediateDirectory)/mm_mm_malloc$(ObjectSuffix) $(IntermediateDirectory)/mm_mm_size2ndx$(ObjectSuffix) $(IntermediateDirectory)/txw4002ack803_pin_function$(ObjectSuffix) $(IntermediateDirectory)/txw4002ack803_system$(ObjectSuffix) $(IntermediateDirectory)/txw4002ack803_trap_c$(ObjectSuffix) \
	$(IntermediateDirectory)/txw4002ack803_vectors$(ObjectSuffix) $(IntermediateDirectory)/txw4002ack803_ticker_api$(ObjectSuffix) $(IntermediateDirectory)/txw4002ack803_dmac_perip_id$(ObjectSuffix) $(IntermediateDirectory)/dma_dw_dmac$(ObjectSuffix) $(IntermediateDirectory)/dma_hg_m2m_dma$(ObjectSuffix) $(IntermediateDirectory)/gpio_hggpio_v2$(ObjectSuffix) $(IntermediateDirectory)/i2c_hgi2c_dw$(ObjectSuffix) $(IntermediateDirectory)/spi_hgspi_dw$(ObjectSuffix) $(IntermediateDirectory)/timer_hgtimer_v2$(ObjectSuffix) $(IntermediateDirectory)/uart_hguart$(ObjectSuffix) \
	$(IntermediateDirectory)/wdt_hg_wdt_v1$(ObjectSuffix) $(IntermediateDirectory)/crc_hg_crc$(ObjectSuffix) $(IntermediateDirectory)/mac_bus_gmac_bus$(ObjectSuffix) $(IntermediateDirectory)/mac_bus_macbus$(ObjectSuffix) $(IntermediateDirectory)/ethernet_phy_eth_phy$(ObjectSuffix) $(IntermediateDirectory)/ethernet_phy_eth_phy_device$(ObjectSuffix) $(IntermediateDirectory)/ethernet_phy_eth_mdio_bus$(ObjectSuffix) $(IntermediateDirectory)/common_common$(ObjectSuffix) $(IntermediateDirectory)/common_string$(ObjectSuffix) $(IntermediateDirectory)/common_sysvar$(ObjectSuffix) \
	$(IntermediateDirectory)/common_us_ticker$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/common_dev$(ObjectSuffix) $(IntermediateDirectory)/common_uart_p2p$(ObjectSuffix) $(IntermediateDirectory)/common_drivercmd$(ObjectSuffix) $(IntermediateDirectory)/spi_nor_spi_nor_bus$(ObjectSuffix) $(IntermediateDirectory)/spi_nor_spi_nor$(ObjectSuffix) $(IntermediateDirectory)/net_utils$(ObjectSuffix) $(IntermediateDirectory)/adapter_csi_rhino$(ObjectSuffix) $(IntermediateDirectory)/common_k_atomic$(ObjectSuffix) $(IntermediateDirectory)/common_k_ffs$(ObjectSuffix) \
	$(IntermediateDirectory)/common_k_fifo$(ObjectSuffix) $(IntermediateDirectory)/common_k_trace$(ObjectSuffix) $(IntermediateDirectory)/core_k_buf_queue$(ObjectSuffix) $(IntermediateDirectory)/core_k_dyn_mem_proc$(ObjectSuffix) $(IntermediateDirectory)/core_k_err$(ObjectSuffix) $(IntermediateDirectory)/core_k_event$(ObjectSuffix) $(IntermediateDirectory)/core_k_idle$(ObjectSuffix) $(IntermediateDirectory)/core_k_mm$(ObjectSuffix) $(IntermediateDirectory)/core_k_mm_blk$(ObjectSuffix) $(IntermediateDirectory)/core_k_mm_debug$(ObjectSuffix) \
	$(IntermediateDirectory)/core_k_mutex$(ObjectSuffix) $(IntermediateDirectory)/core_k_obj$(ObjectSuffix) $(IntermediateDirectory)/core_k_pend$(ObjectSuffix) $(IntermediateDirectory)/core_k_queue$(ObjectSuffix) $(IntermediateDirectory)/core_k_ringbuf$(ObjectSuffix) $(IntermediateDirectory)/core_k_sched$(ObjectSuffix) $(IntermediateDirectory)/core_k_sem$(ObjectSuffix) $(IntermediateDirectory)/core_k_stats$(ObjectSuffix) $(IntermediateDirectory)/core_k_sys$(ObjectSuffix) $(IntermediateDirectory)/core_k_task$(ObjectSuffix) \
	$(IntermediateDirectory)/core_k_task_sem$(ObjectSuffix) $(IntermediateDirectory)/core_k_tick$(ObjectSuffix) $(IntermediateDirectory)/core_k_time$(ObjectSuffix) $(IntermediateDirectory)/core_k_timer$(ObjectSuffix) $(IntermediateDirectory)/core_k_workqueue$(ObjectSuffix) $(IntermediateDirectory)/driver_hook_impl$(ObjectSuffix) $(IntermediateDirectory)/driver_systick$(ObjectSuffix) $(IntermediateDirectory)/driver_yoc_impl$(ObjectSuffix) $(IntermediateDirectory)/driver_hook_weak$(ObjectSuffix) $(IntermediateDirectory)/phy_ip101g$(ObjectSuffix) \
	$(IntermediateDirectory)/phy_rtl8201f$(ObjectSuffix) $(IntermediateDirectory)/phy_sz18201$(ObjectSuffix) $(IntermediateDirectory)/phy_auto_phy$(ObjectSuffix) $(IntermediateDirectory)/csky_cpu_impl$(ObjectSuffix) $(IntermediateDirectory)/csky_csky_sched$(ObjectSuffix) $(IntermediateDirectory)/csky_port_c$(ObjectSuffix) $(IntermediateDirectory)/csky_port_s$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) 

##
## Main Build Targets 
##
.PHONY: all
all: $(IntermediateDirectory)/$(OutputFile)

$(IntermediateDirectory)/$(OutputFile):  $(Objects) Always_Link 
	$(LinkerName) $(OutputSwitch) $(IntermediateDirectory)/$(OutputFile)$(ExeSuffix) $(LinkerNameoption) $(LinkOtherFlagsOption)  -Wl,--ckmap=$(ProjectPath)/Lst/$(OutputFile).map  @$(ObjectsFileList) $(LibraryPathSwitch)C:/nonos/hgSDK-v1.6.4.3-29063-wnb/sdk  -Wl,--whole-archive $(LibrarySwitch)txw4002a   -Wl,--no-whole-archive  $(LinkOptions) $(LibPath) $(Libs)
	@mv $(ProjectPath)/Lst/$(OutputFile).map $(ProjectPath)/Lst/$(OutputFile).temp && $(READELF) $(ElfInfoSwitch) $(ProjectPath)/Obj/$(OutputFile)$(ExeSuffix) > $(ProjectPath)/Lst/$(OutputFile).map && echo ====================================================================== >> $(ProjectPath)/Lst/$(OutputFile).map && cat $(ProjectPath)/Lst/$(OutputFile).temp >> $(ProjectPath)/Lst/$(OutputFile).map && rm -rf $(ProjectPath)/Lst/$(OutputFile).temp
	$(OBJCOPY) $(ObjcopySwitch) $(ProjectPath)/$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix)  $(ProjectPath)/Obj/$(OutputFile)$(IHexSuffix) 
		$(OBJDUMP) $(ObjdumpSwitch) $(ProjectPath)/$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix)  > $(ProjectPath)/Lst/$(OutputFile)$(DisassemSuffix) 
	@echo size of target:
	@$(SIZE) $(ProjectPath)$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix) 
	@echo -n checksum value of target:  
	@$(CHECKSUM) $(ProjectPath)/$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix) 
	@$(ProjectName).modify.bat $(IntermediateDirectory) $(OutputFile)$(ExeSuffix) 

Always_Link:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.c  
	$(CC) $(SourceSwitch) main.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/main$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/main$(PreprocessSuffix) main.c

$(IntermediateDirectory)/device$(ObjectSuffix): device.c  
	$(CC) $(SourceSwitch) device.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/device$(ObjectSuffix) -MF$(IntermediateDirectory)/device$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/device$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/device$(PreprocessSuffix): device.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/device$(PreprocessSuffix) device.c

$(IntermediateDirectory)/hgic_usart$(ObjectSuffix): ../csky/hgic/usart.c  
	$(CC) $(SourceSwitch) ../csky/hgic/usart.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/hgic_usart$(ObjectSuffix) -MF$(IntermediateDirectory)/hgic_usart$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/hgic_usart$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/hgic_usart$(PreprocessSuffix): ../csky/hgic/usart.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/hgic_usart$(PreprocessSuffix) ../csky/hgic/usart.c

$(IntermediateDirectory)/hgic_malloc$(ObjectSuffix): ../csky/hgic/malloc.c  
	$(CC) $(SourceSwitch) ../csky/hgic/malloc.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/hgic_malloc$(ObjectSuffix) -MF$(IntermediateDirectory)/hgic_malloc$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/hgic_malloc$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/hgic_malloc$(PreprocessSuffix): ../csky/hgic/malloc.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/hgic_malloc$(PreprocessSuffix) ../csky/hgic/malloc.c

$(IntermediateDirectory)/hgic_assert$(ObjectSuffix): ../csky/hgic/assert.c  
	$(CC) $(SourceSwitch) ../csky/hgic/assert.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/hgic_assert$(ObjectSuffix) -MF$(IntermediateDirectory)/hgic_assert$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/hgic_assert$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/hgic_assert$(PreprocessSuffix): ../csky/hgic/assert.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/hgic_assert$(PreprocessSuffix) ../csky/hgic/assert.c

$(IntermediateDirectory)/libc_malloc$(ObjectSuffix): ../csky/libs/libc/malloc.c  
	$(CC) $(SourceSwitch) ../csky/libs/libc/malloc.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/libc_malloc$(ObjectSuffix) -MF$(IntermediateDirectory)/libc_malloc$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/libc_malloc$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/libc_malloc$(PreprocessSuffix): ../csky/libs/libc/malloc.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/libc_malloc$(PreprocessSuffix) ../csky/libs/libc/malloc.c

$(IntermediateDirectory)/libc_minilibc_port$(ObjectSuffix): ../csky/libs/libc/minilibc_port.c  
	$(CC) $(SourceSwitch) ../csky/libs/libc/minilibc_port.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/libc_minilibc_port$(ObjectSuffix) -MF$(IntermediateDirectory)/libc_minilibc_port$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/libc_minilibc_port$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/libc_minilibc_port$(PreprocessSuffix): ../csky/libs/libc/minilibc_port.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/libc_minilibc_port$(PreprocessSuffix) ../csky/libs/libc/minilibc_port.c

$(IntermediateDirectory)/mm_dq_addlast$(ObjectSuffix): ../csky/libs/mm/dq_addlast.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/dq_addlast.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_dq_addlast$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_dq_addlast$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_dq_addlast$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_dq_addlast$(PreprocessSuffix): ../csky/libs/mm/dq_addlast.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_dq_addlast$(PreprocessSuffix) ../csky/libs/mm/dq_addlast.c

$(IntermediateDirectory)/mm_dq_rem$(ObjectSuffix): ../csky/libs/mm/dq_rem.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/dq_rem.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_dq_rem$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_dq_rem$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_dq_rem$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_dq_rem$(PreprocessSuffix): ../csky/libs/mm/dq_rem.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_dq_rem$(PreprocessSuffix) ../csky/libs/mm/dq_rem.c

$(IntermediateDirectory)/mm_lib_mallinfo$(ObjectSuffix): ../csky/libs/mm/lib_mallinfo.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/lib_mallinfo.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_lib_mallinfo$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_lib_mallinfo$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_lib_mallinfo$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_lib_mallinfo$(PreprocessSuffix): ../csky/libs/mm/lib_mallinfo.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_lib_mallinfo$(PreprocessSuffix) ../csky/libs/mm/lib_mallinfo.c

$(IntermediateDirectory)/mm_mm_addfreechunk$(ObjectSuffix): ../csky/libs/mm/mm_addfreechunk.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_addfreechunk.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_addfreechunk$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_addfreechunk$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_addfreechunk$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_addfreechunk$(PreprocessSuffix): ../csky/libs/mm/mm_addfreechunk.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_addfreechunk$(PreprocessSuffix) ../csky/libs/mm/mm_addfreechunk.c

$(IntermediateDirectory)/mm_mm_free$(ObjectSuffix): ../csky/libs/mm/mm_free.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_free.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_free$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_free$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_free$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_free$(PreprocessSuffix): ../csky/libs/mm/mm_free.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_free$(PreprocessSuffix) ../csky/libs/mm/mm_free.c

$(IntermediateDirectory)/mm_mm_initialize$(ObjectSuffix): ../csky/libs/mm/mm_initialize.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_initialize.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_initialize$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_initialize$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_initialize$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_initialize$(PreprocessSuffix): ../csky/libs/mm/mm_initialize.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_initialize$(PreprocessSuffix) ../csky/libs/mm/mm_initialize.c

$(IntermediateDirectory)/mm_mm_leak$(ObjectSuffix): ../csky/libs/mm/mm_leak.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_leak.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_leak$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_leak$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_leak$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_leak$(PreprocessSuffix): ../csky/libs/mm/mm_leak.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_leak$(PreprocessSuffix) ../csky/libs/mm/mm_leak.c

$(IntermediateDirectory)/mm_mm_mallinfo$(ObjectSuffix): ../csky/libs/mm/mm_mallinfo.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_mallinfo.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_mallinfo$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_mallinfo$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_mallinfo$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_mallinfo$(PreprocessSuffix): ../csky/libs/mm/mm_mallinfo.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_mallinfo$(PreprocessSuffix) ../csky/libs/mm/mm_mallinfo.c

$(IntermediateDirectory)/mm_mm_malloc$(ObjectSuffix): ../csky/libs/mm/mm_malloc.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_malloc.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_malloc$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_malloc$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_malloc$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_malloc$(PreprocessSuffix): ../csky/libs/mm/mm_malloc.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_malloc$(PreprocessSuffix) ../csky/libs/mm/mm_malloc.c

$(IntermediateDirectory)/mm_mm_size2ndx$(ObjectSuffix): ../csky/libs/mm/mm_size2ndx.c  
	$(CC) $(SourceSwitch) ../csky/libs/mm/mm_size2ndx.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mm_mm_size2ndx$(ObjectSuffix) -MF$(IntermediateDirectory)/mm_mm_size2ndx$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mm_mm_size2ndx$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mm_mm_size2ndx$(PreprocessSuffix): ../csky/libs/mm/mm_size2ndx.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mm_mm_size2ndx$(PreprocessSuffix) ../csky/libs/mm/mm_size2ndx.c

$(IntermediateDirectory)/txw4002ack803_pin_function$(ObjectSuffix): ../sdk/chip/txw4002ack803/pin_function.c  
	$(CC) $(SourceSwitch) ../sdk/chip/txw4002ack803/pin_function.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/txw4002ack803_pin_function$(ObjectSuffix) -MF$(IntermediateDirectory)/txw4002ack803_pin_function$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/txw4002ack803_pin_function$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/txw4002ack803_pin_function$(PreprocessSuffix): ../sdk/chip/txw4002ack803/pin_function.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/txw4002ack803_pin_function$(PreprocessSuffix) ../sdk/chip/txw4002ack803/pin_function.c

$(IntermediateDirectory)/txw4002ack803_system$(ObjectSuffix): ../sdk/chip/txw4002ack803/system.c  
	$(CC) $(SourceSwitch) ../sdk/chip/txw4002ack803/system.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/txw4002ack803_system$(ObjectSuffix) -MF$(IntermediateDirectory)/txw4002ack803_system$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/txw4002ack803_system$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/txw4002ack803_system$(PreprocessSuffix): ../sdk/chip/txw4002ack803/system.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/txw4002ack803_system$(PreprocessSuffix) ../sdk/chip/txw4002ack803/system.c

$(IntermediateDirectory)/txw4002ack803_trap_c$(ObjectSuffix): ../sdk/chip/txw4002ack803/trap_c.c  
	$(CC) $(SourceSwitch) ../sdk/chip/txw4002ack803/trap_c.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/txw4002ack803_trap_c$(ObjectSuffix) -MF$(IntermediateDirectory)/txw4002ack803_trap_c$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/txw4002ack803_trap_c$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/txw4002ack803_trap_c$(PreprocessSuffix): ../sdk/chip/txw4002ack803/trap_c.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/txw4002ack803_trap_c$(PreprocessSuffix) ../sdk/chip/txw4002ack803/trap_c.c

$(IntermediateDirectory)/txw4002ack803_vectors$(ObjectSuffix): ../sdk/chip/txw4002ack803/vectors.S  
	$(AS) $(SourceSwitch) ../sdk/chip/txw4002ack803/vectors.S $(ASFLAGS) -MMD -MP -MT$(IntermediateDirectory)/txw4002ack803_vectors$(ObjectSuffix) -MF$(IntermediateDirectory)/txw4002ack803_vectors$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/txw4002ack803_vectors$(ObjectSuffix) $(IncludeAPath) $(IncludePackagePath)
Lst/txw4002ack803_vectors$(PreprocessSuffix): ../sdk/chip/txw4002ack803/vectors.S
	$(CC) $(CFLAGS)$(IncludeAPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/txw4002ack803_vectors$(PreprocessSuffix) ../sdk/chip/txw4002ack803/vectors.S

$(IntermediateDirectory)/txw4002ack803_ticker_api$(ObjectSuffix): ../sdk/chip/txw4002ack803/ticker_api.c  
	$(CC) $(SourceSwitch) ../sdk/chip/txw4002ack803/ticker_api.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/txw4002ack803_ticker_api$(ObjectSuffix) -MF$(IntermediateDirectory)/txw4002ack803_ticker_api$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/txw4002ack803_ticker_api$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/txw4002ack803_ticker_api$(PreprocessSuffix): ../sdk/chip/txw4002ack803/ticker_api.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/txw4002ack803_ticker_api$(PreprocessSuffix) ../sdk/chip/txw4002ack803/ticker_api.c

$(IntermediateDirectory)/txw4002ack803_dmac_perip_id$(ObjectSuffix): ../sdk/chip/txw4002ack803/dmac_perip_id.c  
	$(CC) $(SourceSwitch) ../sdk/chip/txw4002ack803/dmac_perip_id.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/txw4002ack803_dmac_perip_id$(ObjectSuffix) -MF$(IntermediateDirectory)/txw4002ack803_dmac_perip_id$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/txw4002ack803_dmac_perip_id$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/txw4002ack803_dmac_perip_id$(PreprocessSuffix): ../sdk/chip/txw4002ack803/dmac_perip_id.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/txw4002ack803_dmac_perip_id$(PreprocessSuffix) ../sdk/chip/txw4002ack803/dmac_perip_id.c

$(IntermediateDirectory)/dma_dw_dmac$(ObjectSuffix): ../sdk/driver/dma/dw_dmac.c  
	$(CC) $(SourceSwitch) ../sdk/driver/dma/dw_dmac.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/dma_dw_dmac$(ObjectSuffix) -MF$(IntermediateDirectory)/dma_dw_dmac$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/dma_dw_dmac$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/dma_dw_dmac$(PreprocessSuffix): ../sdk/driver/dma/dw_dmac.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/dma_dw_dmac$(PreprocessSuffix) ../sdk/driver/dma/dw_dmac.c

$(IntermediateDirectory)/dma_hg_m2m_dma$(ObjectSuffix): ../sdk/driver/dma/hg_m2m_dma.c  
	$(CC) $(SourceSwitch) ../sdk/driver/dma/hg_m2m_dma.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/dma_hg_m2m_dma$(ObjectSuffix) -MF$(IntermediateDirectory)/dma_hg_m2m_dma$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/dma_hg_m2m_dma$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/dma_hg_m2m_dma$(PreprocessSuffix): ../sdk/driver/dma/hg_m2m_dma.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/dma_hg_m2m_dma$(PreprocessSuffix) ../sdk/driver/dma/hg_m2m_dma.c

$(IntermediateDirectory)/gpio_hggpio_v2$(ObjectSuffix): ../sdk/driver/gpio/hggpio_v2.c  
	$(CC) $(SourceSwitch) ../sdk/driver/gpio/hggpio_v2.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/gpio_hggpio_v2$(ObjectSuffix) -MF$(IntermediateDirectory)/gpio_hggpio_v2$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/gpio_hggpio_v2$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/gpio_hggpio_v2$(PreprocessSuffix): ../sdk/driver/gpio/hggpio_v2.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/gpio_hggpio_v2$(PreprocessSuffix) ../sdk/driver/gpio/hggpio_v2.c

$(IntermediateDirectory)/i2c_hgi2c_dw$(ObjectSuffix): ../sdk/driver/i2c/hgi2c_dw.c  
	$(CC) $(SourceSwitch) ../sdk/driver/i2c/hgi2c_dw.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/i2c_hgi2c_dw$(ObjectSuffix) -MF$(IntermediateDirectory)/i2c_hgi2c_dw$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/i2c_hgi2c_dw$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/i2c_hgi2c_dw$(PreprocessSuffix): ../sdk/driver/i2c/hgi2c_dw.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/i2c_hgi2c_dw$(PreprocessSuffix) ../sdk/driver/i2c/hgi2c_dw.c

$(IntermediateDirectory)/spi_hgspi_dw$(ObjectSuffix): ../sdk/driver/spi/hgspi_dw.c  
	$(CC) $(SourceSwitch) ../sdk/driver/spi/hgspi_dw.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/spi_hgspi_dw$(ObjectSuffix) -MF$(IntermediateDirectory)/spi_hgspi_dw$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/spi_hgspi_dw$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/spi_hgspi_dw$(PreprocessSuffix): ../sdk/driver/spi/hgspi_dw.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/spi_hgspi_dw$(PreprocessSuffix) ../sdk/driver/spi/hgspi_dw.c

$(IntermediateDirectory)/timer_hgtimer_v2$(ObjectSuffix): ../sdk/driver/timer/hgtimer_v2.c  
	$(CC) $(SourceSwitch) ../sdk/driver/timer/hgtimer_v2.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/timer_hgtimer_v2$(ObjectSuffix) -MF$(IntermediateDirectory)/timer_hgtimer_v2$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/timer_hgtimer_v2$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/timer_hgtimer_v2$(PreprocessSuffix): ../sdk/driver/timer/hgtimer_v2.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/timer_hgtimer_v2$(PreprocessSuffix) ../sdk/driver/timer/hgtimer_v2.c

$(IntermediateDirectory)/uart_hguart$(ObjectSuffix): ../sdk/driver/uart/hguart.c  
	$(CC) $(SourceSwitch) ../sdk/driver/uart/hguart.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/uart_hguart$(ObjectSuffix) -MF$(IntermediateDirectory)/uart_hguart$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/uart_hguart$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/uart_hguart$(PreprocessSuffix): ../sdk/driver/uart/hguart.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/uart_hguart$(PreprocessSuffix) ../sdk/driver/uart/hguart.c

$(IntermediateDirectory)/wdt_hg_wdt_v1$(ObjectSuffix): ../sdk/driver/wdt/hg_wdt_v1.c  
	$(CC) $(SourceSwitch) ../sdk/driver/wdt/hg_wdt_v1.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/wdt_hg_wdt_v1$(ObjectSuffix) -MF$(IntermediateDirectory)/wdt_hg_wdt_v1$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/wdt_hg_wdt_v1$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/wdt_hg_wdt_v1$(PreprocessSuffix): ../sdk/driver/wdt/hg_wdt_v1.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/wdt_hg_wdt_v1$(PreprocessSuffix) ../sdk/driver/wdt/hg_wdt_v1.c

$(IntermediateDirectory)/crc_hg_crc$(ObjectSuffix): ../sdk/driver/crc/hg_crc.c  
	$(CC) $(SourceSwitch) ../sdk/driver/crc/hg_crc.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/crc_hg_crc$(ObjectSuffix) -MF$(IntermediateDirectory)/crc_hg_crc$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/crc_hg_crc$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/crc_hg_crc$(PreprocessSuffix): ../sdk/driver/crc/hg_crc.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/crc_hg_crc$(PreprocessSuffix) ../sdk/driver/crc/hg_crc.c

$(IntermediateDirectory)/mac_bus_gmac_bus$(ObjectSuffix): ../sdk/lib/mac_bus/gmac_bus.c  
	$(CC) $(SourceSwitch) ../sdk/lib/mac_bus/gmac_bus.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mac_bus_gmac_bus$(ObjectSuffix) -MF$(IntermediateDirectory)/mac_bus_gmac_bus$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mac_bus_gmac_bus$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mac_bus_gmac_bus$(PreprocessSuffix): ../sdk/lib/mac_bus/gmac_bus.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mac_bus_gmac_bus$(PreprocessSuffix) ../sdk/lib/mac_bus/gmac_bus.c

$(IntermediateDirectory)/mac_bus_macbus$(ObjectSuffix): ../sdk/lib/mac_bus/macbus.c  
	$(CC) $(SourceSwitch) ../sdk/lib/mac_bus/macbus.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/mac_bus_macbus$(ObjectSuffix) -MF$(IntermediateDirectory)/mac_bus_macbus$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/mac_bus_macbus$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/mac_bus_macbus$(PreprocessSuffix): ../sdk/lib/mac_bus/macbus.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/mac_bus_macbus$(PreprocessSuffix) ../sdk/lib/mac_bus/macbus.c

$(IntermediateDirectory)/ethernet_phy_eth_phy$(ObjectSuffix): ../sdk/lib/ethernet_phy/eth_phy.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/eth_phy.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/ethernet_phy_eth_phy$(ObjectSuffix) -MF$(IntermediateDirectory)/ethernet_phy_eth_phy$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/ethernet_phy_eth_phy$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/ethernet_phy_eth_phy$(PreprocessSuffix): ../sdk/lib/ethernet_phy/eth_phy.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/ethernet_phy_eth_phy$(PreprocessSuffix) ../sdk/lib/ethernet_phy/eth_phy.c

$(IntermediateDirectory)/ethernet_phy_eth_phy_device$(ObjectSuffix): ../sdk/lib/ethernet_phy/eth_phy_device.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/eth_phy_device.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/ethernet_phy_eth_phy_device$(ObjectSuffix) -MF$(IntermediateDirectory)/ethernet_phy_eth_phy_device$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/ethernet_phy_eth_phy_device$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/ethernet_phy_eth_phy_device$(PreprocessSuffix): ../sdk/lib/ethernet_phy/eth_phy_device.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/ethernet_phy_eth_phy_device$(PreprocessSuffix) ../sdk/lib/ethernet_phy/eth_phy_device.c

$(IntermediateDirectory)/ethernet_phy_eth_mdio_bus$(ObjectSuffix): ../sdk/lib/ethernet_phy/eth_mdio_bus.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/eth_mdio_bus.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/ethernet_phy_eth_mdio_bus$(ObjectSuffix) -MF$(IntermediateDirectory)/ethernet_phy_eth_mdio_bus$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/ethernet_phy_eth_mdio_bus$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/ethernet_phy_eth_mdio_bus$(PreprocessSuffix): ../sdk/lib/ethernet_phy/eth_mdio_bus.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/ethernet_phy_eth_mdio_bus$(PreprocessSuffix) ../sdk/lib/ethernet_phy/eth_mdio_bus.c

$(IntermediateDirectory)/common_common$(ObjectSuffix): ../sdk/lib/common/common.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/common.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_common$(ObjectSuffix) -MF$(IntermediateDirectory)/common_common$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_common$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_common$(PreprocessSuffix): ../sdk/lib/common/common.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_common$(PreprocessSuffix) ../sdk/lib/common/common.c

$(IntermediateDirectory)/common_string$(ObjectSuffix): ../sdk/lib/common/string.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/string.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_string$(ObjectSuffix) -MF$(IntermediateDirectory)/common_string$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_string$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_string$(PreprocessSuffix): ../sdk/lib/common/string.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_string$(PreprocessSuffix) ../sdk/lib/common/string.c

$(IntermediateDirectory)/common_sysvar$(ObjectSuffix): ../sdk/lib/common/sysvar.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/sysvar.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_sysvar$(ObjectSuffix) -MF$(IntermediateDirectory)/common_sysvar$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_sysvar$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_sysvar$(PreprocessSuffix): ../sdk/lib/common/sysvar.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_sysvar$(PreprocessSuffix) ../sdk/lib/common/sysvar.c

$(IntermediateDirectory)/common_us_ticker$(ObjectSuffix): ../sdk/lib/common/us_ticker.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/us_ticker.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_us_ticker$(ObjectSuffix) -MF$(IntermediateDirectory)/common_us_ticker$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_us_ticker$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_us_ticker$(PreprocessSuffix): ../sdk/lib/common/us_ticker.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_us_ticker$(PreprocessSuffix) ../sdk/lib/common/us_ticker.c

$(IntermediateDirectory)/common_dev$(ObjectSuffix): ../sdk/lib/common/dev.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/dev.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_dev$(ObjectSuffix) -MF$(IntermediateDirectory)/common_dev$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_dev$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_dev$(PreprocessSuffix): ../sdk/lib/common/dev.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_dev$(PreprocessSuffix) ../sdk/lib/common/dev.c

$(IntermediateDirectory)/common_uart_p2p$(ObjectSuffix): ../sdk/lib/common/uart_p2p.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/uart_p2p.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_uart_p2p$(ObjectSuffix) -MF$(IntermediateDirectory)/common_uart_p2p$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_uart_p2p$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_uart_p2p$(PreprocessSuffix): ../sdk/lib/common/uart_p2p.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_uart_p2p$(PreprocessSuffix) ../sdk/lib/common/uart_p2p.c

$(IntermediateDirectory)/common_drivercmd$(ObjectSuffix): ../sdk/lib/common/drivercmd.c  
	$(CC) $(SourceSwitch) ../sdk/lib/common/drivercmd.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_drivercmd$(ObjectSuffix) -MF$(IntermediateDirectory)/common_drivercmd$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_drivercmd$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_drivercmd$(PreprocessSuffix): ../sdk/lib/common/drivercmd.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_drivercmd$(PreprocessSuffix) ../sdk/lib/common/drivercmd.c

$(IntermediateDirectory)/spi_nor_spi_nor_bus$(ObjectSuffix): ../sdk/lib/spi_nor/spi_nor_bus.c  
	$(CC) $(SourceSwitch) ../sdk/lib/spi_nor/spi_nor_bus.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/spi_nor_spi_nor_bus$(ObjectSuffix) -MF$(IntermediateDirectory)/spi_nor_spi_nor_bus$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/spi_nor_spi_nor_bus$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/spi_nor_spi_nor_bus$(PreprocessSuffix): ../sdk/lib/spi_nor/spi_nor_bus.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/spi_nor_spi_nor_bus$(PreprocessSuffix) ../sdk/lib/spi_nor/spi_nor_bus.c

$(IntermediateDirectory)/spi_nor_spi_nor$(ObjectSuffix): ../sdk/lib/spi_nor/spi_nor.c  
	$(CC) $(SourceSwitch) ../sdk/lib/spi_nor/spi_nor.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/spi_nor_spi_nor$(ObjectSuffix) -MF$(IntermediateDirectory)/spi_nor_spi_nor$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/spi_nor_spi_nor$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/spi_nor_spi_nor$(PreprocessSuffix): ../sdk/lib/spi_nor/spi_nor.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/spi_nor_spi_nor$(PreprocessSuffix) ../sdk/lib/spi_nor/spi_nor.c

$(IntermediateDirectory)/net_utils$(ObjectSuffix): ../sdk/lib/net/utils.c  
	$(CC) $(SourceSwitch) ../sdk/lib/net/utils.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/net_utils$(ObjectSuffix) -MF$(IntermediateDirectory)/net_utils$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/net_utils$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/net_utils$(PreprocessSuffix): ../sdk/lib/net/utils.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/net_utils$(PreprocessSuffix) ../sdk/lib/net/utils.c

$(IntermediateDirectory)/adapter_csi_rhino$(ObjectSuffix): ../csky/csi_kernel/rhino/adapter/csi_rhino.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/adapter/csi_rhino.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/adapter_csi_rhino$(ObjectSuffix) -MF$(IntermediateDirectory)/adapter_csi_rhino$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/adapter_csi_rhino$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/adapter_csi_rhino$(PreprocessSuffix): ../csky/csi_kernel/rhino/adapter/csi_rhino.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/adapter_csi_rhino$(PreprocessSuffix) ../csky/csi_kernel/rhino/adapter/csi_rhino.c

$(IntermediateDirectory)/common_k_atomic$(ObjectSuffix): ../csky/csi_kernel/rhino/common/k_atomic.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/common/k_atomic.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_k_atomic$(ObjectSuffix) -MF$(IntermediateDirectory)/common_k_atomic$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_k_atomic$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_k_atomic$(PreprocessSuffix): ../csky/csi_kernel/rhino/common/k_atomic.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_k_atomic$(PreprocessSuffix) ../csky/csi_kernel/rhino/common/k_atomic.c

$(IntermediateDirectory)/common_k_ffs$(ObjectSuffix): ../csky/csi_kernel/rhino/common/k_ffs.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/common/k_ffs.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_k_ffs$(ObjectSuffix) -MF$(IntermediateDirectory)/common_k_ffs$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_k_ffs$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_k_ffs$(PreprocessSuffix): ../csky/csi_kernel/rhino/common/k_ffs.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_k_ffs$(PreprocessSuffix) ../csky/csi_kernel/rhino/common/k_ffs.c

$(IntermediateDirectory)/common_k_fifo$(ObjectSuffix): ../csky/csi_kernel/rhino/common/k_fifo.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/common/k_fifo.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_k_fifo$(ObjectSuffix) -MF$(IntermediateDirectory)/common_k_fifo$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_k_fifo$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_k_fifo$(PreprocessSuffix): ../csky/csi_kernel/rhino/common/k_fifo.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_k_fifo$(PreprocessSuffix) ../csky/csi_kernel/rhino/common/k_fifo.c

$(IntermediateDirectory)/common_k_trace$(ObjectSuffix): ../csky/csi_kernel/rhino/common/k_trace.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/common/k_trace.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/common_k_trace$(ObjectSuffix) -MF$(IntermediateDirectory)/common_k_trace$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/common_k_trace$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/common_k_trace$(PreprocessSuffix): ../csky/csi_kernel/rhino/common/k_trace.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/common_k_trace$(PreprocessSuffix) ../csky/csi_kernel/rhino/common/k_trace.c

$(IntermediateDirectory)/core_k_buf_queue$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_buf_queue.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_buf_queue.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_buf_queue$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_buf_queue$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_buf_queue$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_buf_queue$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_buf_queue.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_buf_queue$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_buf_queue.c

$(IntermediateDirectory)/core_k_dyn_mem_proc$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_dyn_mem_proc.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_dyn_mem_proc.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_dyn_mem_proc$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_dyn_mem_proc$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_dyn_mem_proc$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_dyn_mem_proc$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_dyn_mem_proc.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_dyn_mem_proc$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_dyn_mem_proc.c

$(IntermediateDirectory)/core_k_err$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_err.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_err.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_err$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_err$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_err$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_err$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_err.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_err$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_err.c

$(IntermediateDirectory)/core_k_event$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_event.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_event.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_event$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_event$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_event$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_event$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_event.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_event$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_event.c

$(IntermediateDirectory)/core_k_idle$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_idle.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_idle.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_idle$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_idle$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_idle$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_idle$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_idle.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_idle$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_idle.c

$(IntermediateDirectory)/core_k_mm$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_mm.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_mm.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_mm$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_mm$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_mm$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_mm$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_mm.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_mm$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_mm.c

$(IntermediateDirectory)/core_k_mm_blk$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_mm_blk.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_mm_blk.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_mm_blk$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_mm_blk$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_mm_blk$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_mm_blk$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_mm_blk.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_mm_blk$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_mm_blk.c

$(IntermediateDirectory)/core_k_mm_debug$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_mm_debug.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_mm_debug.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_mm_debug$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_mm_debug$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_mm_debug$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_mm_debug$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_mm_debug.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_mm_debug$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_mm_debug.c

$(IntermediateDirectory)/core_k_mutex$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_mutex.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_mutex.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_mutex$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_mutex$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_mutex$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_mutex$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_mutex.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_mutex$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_mutex.c

$(IntermediateDirectory)/core_k_obj$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_obj.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_obj.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_obj$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_obj$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_obj$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_obj$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_obj.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_obj$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_obj.c

$(IntermediateDirectory)/core_k_pend$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_pend.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_pend.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_pend$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_pend$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_pend$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_pend$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_pend.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_pend$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_pend.c

$(IntermediateDirectory)/core_k_queue$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_queue.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_queue.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_queue$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_queue$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_queue$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_queue$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_queue.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_queue$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_queue.c

$(IntermediateDirectory)/core_k_ringbuf$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_ringbuf.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_ringbuf.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_ringbuf$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_ringbuf$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_ringbuf$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_ringbuf$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_ringbuf.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_ringbuf$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_ringbuf.c

$(IntermediateDirectory)/core_k_sched$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_sched.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_sched.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_sched$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_sched$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_sched$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_sched$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_sched.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_sched$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_sched.c

$(IntermediateDirectory)/core_k_sem$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_sem.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_sem.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_sem$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_sem$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_sem$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_sem$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_sem.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_sem$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_sem.c

$(IntermediateDirectory)/core_k_stats$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_stats.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_stats.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_stats$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_stats$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_stats$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_stats$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_stats.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_stats$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_stats.c

$(IntermediateDirectory)/core_k_sys$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_sys.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_sys.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_sys$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_sys$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_sys$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_sys$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_sys.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_sys$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_sys.c

$(IntermediateDirectory)/core_k_task$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_task.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_task.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_task$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_task$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_task$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_task$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_task.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_task$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_task.c

$(IntermediateDirectory)/core_k_task_sem$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_task_sem.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_task_sem.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_task_sem$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_task_sem$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_task_sem$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_task_sem$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_task_sem.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_task_sem$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_task_sem.c

$(IntermediateDirectory)/core_k_tick$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_tick.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_tick.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_tick$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_tick$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_tick$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_tick$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_tick.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_tick$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_tick.c

$(IntermediateDirectory)/core_k_time$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_time.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_time.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_time$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_time$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_time$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_time$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_time.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_time$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_time.c

$(IntermediateDirectory)/core_k_timer$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_timer.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_timer.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_timer$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_timer$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_timer$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_timer$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_timer.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_timer$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_timer.c

$(IntermediateDirectory)/core_k_workqueue$(ObjectSuffix): ../csky/csi_kernel/rhino/core/k_workqueue.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/core/k_workqueue.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/core_k_workqueue$(ObjectSuffix) -MF$(IntermediateDirectory)/core_k_workqueue$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/core_k_workqueue$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/core_k_workqueue$(PreprocessSuffix): ../csky/csi_kernel/rhino/core/k_workqueue.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/core_k_workqueue$(PreprocessSuffix) ../csky/csi_kernel/rhino/core/k_workqueue.c

$(IntermediateDirectory)/driver_hook_impl$(ObjectSuffix): ../csky/csi_kernel/rhino/driver/hook_impl.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/driver/hook_impl.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/driver_hook_impl$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_hook_impl$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/driver_hook_impl$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/driver_hook_impl$(PreprocessSuffix): ../csky/csi_kernel/rhino/driver/hook_impl.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/driver_hook_impl$(PreprocessSuffix) ../csky/csi_kernel/rhino/driver/hook_impl.c

$(IntermediateDirectory)/driver_systick$(ObjectSuffix): ../csky/csi_kernel/rhino/driver/systick.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/driver/systick.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/driver_systick$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_systick$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/driver_systick$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/driver_systick$(PreprocessSuffix): ../csky/csi_kernel/rhino/driver/systick.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/driver_systick$(PreprocessSuffix) ../csky/csi_kernel/rhino/driver/systick.c

$(IntermediateDirectory)/driver_yoc_impl$(ObjectSuffix): ../csky/csi_kernel/rhino/driver/yoc_impl.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/driver/yoc_impl.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/driver_yoc_impl$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_yoc_impl$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/driver_yoc_impl$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/driver_yoc_impl$(PreprocessSuffix): ../csky/csi_kernel/rhino/driver/yoc_impl.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/driver_yoc_impl$(PreprocessSuffix) ../csky/csi_kernel/rhino/driver/yoc_impl.c

$(IntermediateDirectory)/driver_hook_weak$(ObjectSuffix): ../csky/csi_kernel/rhino/driver/hook_weak.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/driver/hook_weak.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/driver_hook_weak$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_hook_weak$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/driver_hook_weak$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/driver_hook_weak$(PreprocessSuffix): ../csky/csi_kernel/rhino/driver/hook_weak.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/driver_hook_weak$(PreprocessSuffix) ../csky/csi_kernel/rhino/driver/hook_weak.c

$(IntermediateDirectory)/phy_ip101g$(ObjectSuffix): ../sdk/lib/ethernet_phy/phy/ip101g.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/phy/ip101g.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/phy_ip101g$(ObjectSuffix) -MF$(IntermediateDirectory)/phy_ip101g$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/phy_ip101g$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/phy_ip101g$(PreprocessSuffix): ../sdk/lib/ethernet_phy/phy/ip101g.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/phy_ip101g$(PreprocessSuffix) ../sdk/lib/ethernet_phy/phy/ip101g.c

$(IntermediateDirectory)/phy_rtl8201f$(ObjectSuffix): ../sdk/lib/ethernet_phy/phy/rtl8201f.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/phy/rtl8201f.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/phy_rtl8201f$(ObjectSuffix) -MF$(IntermediateDirectory)/phy_rtl8201f$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/phy_rtl8201f$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/phy_rtl8201f$(PreprocessSuffix): ../sdk/lib/ethernet_phy/phy/rtl8201f.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/phy_rtl8201f$(PreprocessSuffix) ../sdk/lib/ethernet_phy/phy/rtl8201f.c

$(IntermediateDirectory)/phy_sz18201$(ObjectSuffix): ../sdk/lib/ethernet_phy/phy/sz18201.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/phy/sz18201.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/phy_sz18201$(ObjectSuffix) -MF$(IntermediateDirectory)/phy_sz18201$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/phy_sz18201$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/phy_sz18201$(PreprocessSuffix): ../sdk/lib/ethernet_phy/phy/sz18201.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/phy_sz18201$(PreprocessSuffix) ../sdk/lib/ethernet_phy/phy/sz18201.c

$(IntermediateDirectory)/phy_auto_phy$(ObjectSuffix): ../sdk/lib/ethernet_phy/phy/auto_phy.c  
	$(CC) $(SourceSwitch) ../sdk/lib/ethernet_phy/phy/auto_phy.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/phy_auto_phy$(ObjectSuffix) -MF$(IntermediateDirectory)/phy_auto_phy$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/phy_auto_phy$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/phy_auto_phy$(PreprocessSuffix): ../sdk/lib/ethernet_phy/phy/auto_phy.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/phy_auto_phy$(PreprocessSuffix) ../sdk/lib/ethernet_phy/phy/auto_phy.c

$(IntermediateDirectory)/csky_cpu_impl$(ObjectSuffix): ../csky/csi_kernel/rhino/arch/csky/cpu_impl.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/arch/csky/cpu_impl.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/csky_cpu_impl$(ObjectSuffix) -MF$(IntermediateDirectory)/csky_cpu_impl$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/csky_cpu_impl$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/csky_cpu_impl$(PreprocessSuffix): ../csky/csi_kernel/rhino/arch/csky/cpu_impl.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/csky_cpu_impl$(PreprocessSuffix) ../csky/csi_kernel/rhino/arch/csky/cpu_impl.c

$(IntermediateDirectory)/csky_csky_sched$(ObjectSuffix): ../csky/csi_kernel/rhino/arch/csky/csky_sched.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/arch/csky/csky_sched.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/csky_csky_sched$(ObjectSuffix) -MF$(IntermediateDirectory)/csky_csky_sched$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/csky_csky_sched$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/csky_csky_sched$(PreprocessSuffix): ../csky/csi_kernel/rhino/arch/csky/csky_sched.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/csky_csky_sched$(PreprocessSuffix) ../csky/csi_kernel/rhino/arch/csky/csky_sched.c

$(IntermediateDirectory)/csky_port_c$(ObjectSuffix): ../csky/csi_kernel/rhino/arch/csky/port_c.c  
	$(CC) $(SourceSwitch) ../csky/csi_kernel/rhino/arch/csky/port_c.c $(CFLAGS) -MMD -MP -MT$(IntermediateDirectory)/csky_port_c$(ObjectSuffix) -MF$(IntermediateDirectory)/csky_port_c$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/csky_port_c$(ObjectSuffix) $(IncludeCPath) $(IncludePackagePath)
Lst/csky_port_c$(PreprocessSuffix): ../csky/csi_kernel/rhino/arch/csky/port_c.c
	$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/csky_port_c$(PreprocessSuffix) ../csky/csi_kernel/rhino/arch/csky/port_c.c

$(IntermediateDirectory)/csky_port_s$(ObjectSuffix): ../csky/csi_kernel/rhino/arch/csky/port_s.S  
	$(AS) $(SourceSwitch) ../csky/csi_kernel/rhino/arch/csky/port_s.S $(ASFLAGS) -MMD -MP -MT$(IntermediateDirectory)/csky_port_s$(ObjectSuffix) -MF$(IntermediateDirectory)/csky_port_s$(DependSuffix) $(ObjectSwitch)$(IntermediateDirectory)/csky_port_s$(ObjectSuffix) $(IncludeAPath) $(IncludePackagePath)
Lst/csky_port_s$(PreprocessSuffix): ../csky/csi_kernel/rhino/arch/csky/port_s.S
	$(CC) $(CFLAGS)$(IncludeAPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/csky_port_s$(PreprocessSuffix) ../csky/csi_kernel/rhino/arch/csky/port_s.S


$(IntermediateDirectory)/__rt_entry$(ObjectSuffix): $(IntermediateDirectory)/__rt_entry$(DependSuffix)
	@$(AS) $(SourceSwitch) $(ProjectPath)/$(IntermediateDirectory)/__rt_entry.S $(ASFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/__rt_entry$(ObjectSuffix) $(IncludeAPath)
$(IntermediateDirectory)/__rt_entry$(DependSuffix):
	@$(CC) $(CFLAGS) $(IncludeAPath) -MG -MP -MT$(IntermediateDirectory)/__rt_entry$(ObjectSuffix) -MF$(IntermediateDirectory)/__rt_entry$(DependSuffix) -MM $(ProjectPath)/$(IntermediateDirectory)/__rt_entry.S

-include $(IntermediateDirectory)/*$(DependSuffix)
