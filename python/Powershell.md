# 解决powershell无法激活conda虚拟环境
- 管理员方式打开powershell
- 执行 `conda init powershell`
- 重新打开powershell，显示base则成功，否则执行下一步
- 执行`get-ExecutionPolicy`显示`Restricted`，表示状态是禁止的。执行`set-ExecutionPolicy RemoteSigned`