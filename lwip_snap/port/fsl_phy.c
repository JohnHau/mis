/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phy.h"
//#include "fsl_debug_console.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 100000

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
extern uint32_t ENET_GetInstance(ENET_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
extern clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_ENET_COUNT];
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

//KSZ8863 switch registers
#define KSZ8863_SW_REG_GLOBAL_CTRL1         3
#define KSZ8863_SW_REG_PORT_CTRL2(n)        (18 + (((n) - 1) * 16))
#define KSZ8863_SW_REG_PORT_STAT0(n)        (30 + (((n) - 1) * 16))
#define KSZ8863_SW_REG_PORT_STAT1(n)        (31 + (((n) - 1) * 16))

//Global control 1 register
#define GLOBAL_CTRL1_PASS_ALL_FRAMES        (1 << 7)
#define GLOBAL_CTRL1_TAIL_TAG_EN            (1 << 6)
#define GLOBAL_CTRL1_TX_FLOW_CTRL_EN        (1 << 5)
#define GLOBAL_CTRL1_RX_FLOW_CTRL_EN        (1 << 4)
#define GLOBAL_CTRL1_FRAME_LEN_CHECK_EN     (1 << 3)
#define GLOBAL_CTRL1_AGING_EN               (1 << 2)
#define GLOBAL_CTRL1_FAST_AGE_EN            (1 << 1)
#define GLOBAL_CTRL1_AGGRESSIVE_BACK_OFF_EN (1 << 0)

//KSZ8863 ports
#define KSZ8863_PORT1                       1
#define KSZ8863_PORT2                       2



//Port control 2 register
#define PORT_CTRL2_TX_QUEUE_SPLIT_EN        (1 << 7)
#define PORT_CTRL2_INGRESS_VLAN_FILT        (1 << 6)
#define PORT_CTRL2_DISCARD_NON_PVID_PACKETS (1 << 5)
#define PORT_CTRL2_FORCE_FLOW_CTRL          (1 << 4)
#define PORT_CTRL2_BACK_PRESSURE_EN         (1 << 3)
#define PORT_CTRL2_TRANSMIT_EN              (1 << 2)
#define PORT_CTRL2_RECEIVE_EN               (1 << 1)
#define PORT_CTRL2_LEARNING_DIS             (1 << 0)

//Port status 0 register
#define PORT_STAT0_MDIX_STATUS              (1 << 7)
#define PORT_STAT0_AN_DONE                  (1 << 6)
#define PORT_STAT0_LINK_GOOD                (1 << 5)
#define PORT_STAT0_LP_FLOW_CTRL_CAPABLE     (1 << 4)
#define PORT_STAT0_100BT_FD_CAPABLE         (1 << 3)
#define PORT_STAT0_100BT_HF_CAPABLE         (1 << 2)
#define PORT_STAT0_10BT_FD_CAPABLE          (1 << 1)
#define PORT_STAT0_10BT_HD_CAPABLE          (1 << 0)

//Port status 1 register
#define PORT_STAT1_HP_MDIX                  (1 << 7)
#define PORT_STAT1_POLRVS                   (1 << 5)
#define PORT_STAT1_TX_FLOW_CTRL_EN          (1 << 4)
#define PORT_STAT1_RX_FLOW_CTRL_EN          (1 << 3)
#define PORT_STAT1_OP_SPEED                 (1 << 2)
#define PORT_STAT1_OP_MODE                  (1 << 1)
#define PORT_STAT1_FAR_END_FAULT            (1 << 0)
/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t bssReg;
    uint32_t counter  = PHY_TIMEOUT_COUNT;
    uint32_t idReg    = 0;
    status_t result   = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);
    uint32_t timeDelay;
    uint32_t ctlReg = 0;
    uint32_t port;
    uint8_t temp;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    //srcClock_Hz =528000000;
    ENET_SetSMI(base, srcClock_Hz, false);
    //return kStatus_Success;
    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        PHY_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        counter--;
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result  = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {


        /* Set the negotiation. */
       result =
                PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
       // result = PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
         //                  (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
          //                  PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
           return kStatus_Success;
          //result = PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
            //               (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
              //              PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
            //result =
            //    PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            if (result == kStatus_Success)
            {
                /* Check auto negotiation complete. */
                while (counter--)
                {
                    
                    if (result == kStatus_Success)
                    {
                        //PHY_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
                        //PRINTF(" SBMR1 IS %x\r\n",bssReg);
                        //if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & PHY_LINK_READY_MASK))
                        if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (bssReg & PHY_BSTATUS_LINKSTATUS_MASK))    
                        {
                            /* Wait a moment for Phy status stable. */
                            for (timeDelay = 0; timeDelay < PHY_TIMEOUT_COUNT; timeDelay++)
                            {
                                __ASM("nop");
                            }
                            //PRINTF("11111 SBMR1 IS %x\r\n",bssReg);
                            break;
                        }
                    }

                    if (!counter)
                    {
                        //PRINTF(" SBMR1 IS %x\r\n",bssReg);
                        return kStatus_PHY_AutoNegotiateFail;
                    }
                }
            }
        }
    }
    return result;
}


status_t PHY_Init1(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
     uint32_t bssReg;
    uint32_t counter  = PHY_TIMEOUT_COUNT;
    uint32_t idReg    = 0;
    status_t result   = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);
    uint32_t timeDelay;
    uint32_t ctlReg = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    ENET_SetSMI(base, srcClock_Hz, false);

    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        PHY_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        counter--;
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result  = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {
       return kStatus_Success;
//#if defined(FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE)
//        uint32_t data = 0;
//        result        = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
//        if (result != kStatus_Success)
//        {
//            return result;
//        }
//        result = PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data | PHY_CTL2_REFCLK_SELECT_MASK));
//        if (result != kStatus_Success)
//        {
//            return result;
//        }
//#endif /* FSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE */

        /* Set the negotiation. */
        result = PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result =
                PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            if (result == kStatus_Success)
            {
                /* Check auto negotiation complete. */
                while (counter--)
                {
                    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &bssReg);
                    if (result == kStatus_Success)
                    {
                        //PHY_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
                        //if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (ctlReg & PHY_LINK_READY_MASK))
                        if (((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0) && (bssReg & PHY_BSTATUS_LINKSTATUS_MASK))    
                        {
                            /* Wait a moment for Phy status stable. */
                            for (timeDelay = 0; timeDelay < PHY_TIMEOUT_COUNT; timeDelay++)
                            {
                                __ASM("nop");
                            }
                            break;
                        }
                    }

                    if (!counter)
                    {
                        return kStatus_PHY_AutoNegotiateFail;
                    }
                }
            }
        }
    }

    return result;
}


status_t PHY_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(base, phyAddr, phyReg, kENET_MiiWriteValidFrame, data);

    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}
#if 0
status_t PHY_EX_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    //ENET_StartSMIWrite(base, phyAddr, phyReg, kENET_MiiWriteValidFrame, data);
    ENET_StartExtC45SMIWrite(base, phyAddr, phyReg, data);
    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}
#endif

status_t PHY_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
    assert(dataPtr);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(base, phyAddr, phyReg, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Get data from MII register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}

#if 0
status_t PHY_EX_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
    assert(dataPtr);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    //ENET_StartSMIRead(base, phyAddr, phyReg, kENET_MiiReadValidFrame);
    
    ENET_StartExtC45SMIRead(base,phyAddr, phyReg);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Get data from MII register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    return kStatus_Success;
}
#endif
status_t PHY_EnableLoopback(ENET_Type *base, uint32_t phyAddr, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    status_t result;
    uint32_t data = 0;

    /* Set the loop mode. */
    if (enable)
    {
        if (mode == kPHY_LocalLoop)
        {
            if (speed == kPHY_Speed100M)
            {
                data = PHY_BCTL_SPEED_100M_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                data = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            return PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, data);
        }
        else
        {
            /* First read the current status in control register. */
            result = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
            if (result == kStatus_Success)
            {
                return PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data | PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = PHY_Read(base, phyAddr, PHY_BASICCONTROL_REG, &data);
            if (result == kStatus_Success)
            {
                data &= ~PHY_BCTL_LOOP_MASK;
                return PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (data | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else
        {
            /* First read the current status in control one register. */
            result = PHY_Read(base, phyAddr, PHY_CONTROL2_REG, &data);
            if (result == kStatus_Success)
            {
                return PHY_Write(base, phyAddr, PHY_CONTROL2_REG, (data & ~PHY_CTL2_REMOTELOOP_MASK));
            }
        }
    }
    return result;
}

status_t PHY_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &data);
    if (result == kStatus_Success)
    {
        if (!(PHY_BSTATUS_LINKSTATUS_MASK & data))
        {
            /* link down. */
            *status = false;
        }
        else
        {
            /* link up. */
            *status = true;
        }
    }
    return result;
}

status_t PHY_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

    /* Read the control two register. */
    result = PHY_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
    if (result == kStatus_Success)
    {
        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_10FULLDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_100HALFDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* 100M speed. */
            *speed = kPHY_Speed100M;
        }
        else
        { /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
    }

    return result;
}
