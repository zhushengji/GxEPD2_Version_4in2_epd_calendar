  ![图片](https://user-images.githubusercontent.com/32239713/151153571-9d4c58d6-e5b2-4a16-8c9d-78818740d7ac.png)
  作者：夏襄居士<br>
  最后更新时间：2022年1月24日15:47<br>
  **已知bug**<br>
        1.轻度休眠重启后有概率导致联网失败，可采取delay方式延迟，但相应的，功耗会增加<br>
        2.强制门户认证有概率无法正常进入，可能跟手机有关<br>
        3.知乎热榜有概率显示过线，这个与接口返回的json数据有关，后期将更新接口以修复<br>
  ### 1.本程序适用微雪4.2寸三色屏,如果是其它品牌的三色屏，修改对应的三色屏display对象及对应接线方式即可。
  ### 2.通用驱动板接线：
        busy---4
        res---rx2
        dc---tx2
        cs---5
        clk---18
        din---23
        gnd---gnd
        vcc---3.3v
        
       
   ### 效果预览
   
  ![1af0bee11542e0579c2ff4943c47163](https://user-images.githubusercontent.com/32239713/151149910-c088d367-e442-4a41-b298-82bd4fbae2c5.jpg)
![f842173f95e6142eef0b99db7b8462d](https://user-images.githubusercontent.com/32239713/151149918-8236e788-cae0-4abc-b710-c04b2347994e.jpg)
![15cd0b2a9cf7e1b60263ce77f4eff5c](https://user-images.githubusercontent.com/32239713/151150139-ccc7a3f2-4db1-4eb9-90e7-21421451060e.jpg)
![Uploading 3c46b13070e9a913b4ea86d16cdeb32.jpg…]()

