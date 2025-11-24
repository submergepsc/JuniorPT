# extract_pptx_to_md_and_cpp.ps1
# 从 13-19 目录的 pptx 提取文本，生成 summary.md，并根据检测到的问题生成 problemNN.cpp
param(
    [string]$BaseDir = 'C:\Users\15056\Desktop\code\JuniorPT\13-19'
)

Function SafeWrite([string]$path, [string]$content){
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($content)
    [System.IO.File]::WriteAllBytes($path, $bytes)
}

$files = Get-ChildItem -Path $BaseDir -Filter *.pptx -File -ErrorAction SilentlyContinue
if (!$files -or $files.Count -eq 0){ Write-Host "未在 $BaseDir 找到任何 pptx 文件。退出。"; exit 0 }

# 尝试使用 PowerPoint COM 提取文本
$pp = $null
try{
    $pp = New-Object -ComObject PowerPoint.Application
} catch {
    Write-Host "无法创建 PowerPoint COM 对象。请确认本机已安装 Microsoft PowerPoint。脚本将退出。"; exit 1
}

foreach ($f in $files){
    Write-Host "处理: $($f.FullName)"
    try{
        $pres = $pp.Presentations.Open($f.FullName, $false, $true, $false)
    } catch {
        Write-Host "无法打开演示文稿： $($f.FullName) -> $_"; continue
    }

    # 根据文件名中的数字决定目标子目录（pt13..pt19），否则使用文件名作为目录名
    $num = ''
    if ($f.BaseName -match '(\d{1,2})') { $num = $matches[0] }
    if ($num) { $outDir = Join-Path $BaseDir ("pt$num") } else { $outDir = Join-Path $BaseDir $f.BaseName }
    if (!(Test-Path $outDir)) { New-Item -ItemType Directory -Force -Path $outDir | Out-Null }

    $mdPath = Join-Path $outDir 'summary.md'
    $sb = New-Object System.Text.StringBuilder
    $sb.AppendLine("# $($f.BaseName)") | Out-Null
    $slideIndex = 1
    foreach ($s in $pres.Slides){
        $sb.AppendLine("\n## Slide $slideIndex") | Out-Null
        foreach ($sh in $s.Shapes){
            try{
                if ($sh.HasTextFrame -and $sh.TextFrame.HasText){
                    $txt = $sh.TextFrame.TextRange.Text -replace "\r\n","\n"
                    $sb.AppendLine($txt) | Out-Null
                }
            } catch {}
        }
        # notes
        try{
            $notesText = ""
            foreach ($ns in $s.NotesPage.Shapes){
                if ($ns.HasTextFrame -and $ns.TextFrame.HasText){ $notesText += $ns.TextFrame.TextRange.Text + "\n" }
            }
            if ($notesText.Trim() -ne ""){
                $sb.AppendLine("\n### Notes") | Out-Null
                $sb.AppendLine($notesText) | Out-Null
            }
        } catch {}
        $slideIndex++
    }
    $pres.Close()

    # 保存 summary.md
    SafeWrite $mdPath $sb.ToString()

    # 从文本中检测题目行（简单启发式规则）
    $text = $sb.ToString()
    $lines = $text -split "`n"
    $problems = @()
    foreach ($line in $lines){
        $trim = $line.Trim()
        if ($trim -match '^\s*(\d{1,2})[\.、\)]') { $problems += $trim; continue }
        if ($trim -match '题' -and $trim.Length -lt 200 -and $trim -notmatch '^##') { $problems += $trim }
    }
    $problems = $problems | Where-Object { $_ -ne '' } | Select-Object -Unique

    # 为每个检测到的问题生成 problemNN.cpp（模板）并在 summary.md 中追加 Solutions 段落
    $solutions = "\n\n## Detected Problems (`($problems.Count)`)\n\n"
    $i = 1
    foreach ($p in $problems){
        $fname = Join-Path $outDir ("problem{0:00}.cpp" -f $i)
        $algo = "算法/思路：在此写出解题思路（脚本自动生成的是模板，请人工检查并根据题目补充输入/输出格式）。"
        $code = @"// $p

#include <bits/stdc++.h>
using namespace std;

int main(){
    // $algo
    return 0;
}
"@
        SafeWrite $fname $code
        $solutions += "### Problem $i\n$p\n\n````cpp\n$code\n````\n\n说明：$algo\n\n"
        $i++
    }

    Add-Content -Path $mdPath -Value $solutions -Encoding UTF8
    Write-Host "已为 $($f.Name) 生成 summary 和 $($problems.Count) 个 problemNN.cpp (放在 $outDir)"
}

$pp.Quit()
Write-Host "全部完成。"
