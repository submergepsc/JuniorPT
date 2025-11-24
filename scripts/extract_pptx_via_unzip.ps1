# extract_pptx_via_unzip.ps1
# 使用 Expand-Archive 解压 pptx（pptx 本质上是 zip），从 slide xml 中提取文本，生成 summary.md 与 problemNN.cpp
param(
    [string]$BaseDir = 'C:\Users\15056\Desktop\code\JuniorPT\13-19'
)

Function SafeWrite([string]$path, [string]$content){
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($content)
    [System.IO.File]::WriteAllBytes($path, $bytes)
}

$files = Get-ChildItem -Path $BaseDir -Recurse -Filter *.pptx -File -ErrorAction SilentlyContinue
if (!$files -or $files.Count -eq 0){ Write-Host "未在 $BaseDir 及其子目录找到任何 pptx 文件。退出。"; exit 0 }

foreach ($f in $files){
    Write-Host "处理: $($f.FullName)"
    $tmp = Join-Path $env:TEMP ([guid]::NewGuid().ToString())
    New-Item -ItemType Directory -Force -Path $tmp | Out-Null
    try{
        Expand-Archive -Path $f.FullName -DestinationPath $tmp -Force -ErrorAction Stop
    } catch {
        Write-Host "无法解压 $($f.FullName) : $_"; Remove-Item -Recurse -Force $tmp -ErrorAction SilentlyContinue; continue
    }

    $outDir = $f.DirectoryName
    if (!(Test-Path $outDir)) { New-Item -ItemType Directory -Force -Path $outDir | Out-Null }
    $mdPath = Join-Path $outDir 'summary.md'
    $sb = New-Object System.Text.StringBuilder
    $sb.AppendLine("# $($f.BaseName)") | Out-Null

    $slidesDir = Join-Path $tmp 'ppt\slides'
    $slideFiles = @()
    if (Test-Path $slidesDir){
        $slideFiles = Get-ChildItem -Path $slidesDir -Filter 'slide*.xml' -File -ErrorAction SilentlyContinue | Sort-Object Name
    }

    $idx = 1
    foreach ($sf in $slideFiles){
        $sb.AppendLine("\n## Slide $idx") | Out-Null
        try{
            $nodes = Select-Xml -Path $sf.FullName -XPath '//a:t' -ErrorAction SilentlyContinue
            foreach ($n in $nodes){ $sb.AppendLine($n.Node.InnerText) | Out-Null }
        } catch {}
        # notes
        $notesDir = Join-Path $tmp 'ppt\notesSlides'
        $notesPath = Join-Path $notesDir ("notesSlide$idx.xml")
        if (Test-Path $notesPath){
            $notes = Select-Xml -Path $notesPath -XPath '//a:t' -ErrorAction SilentlyContinue
            if ($notes){ $sb.AppendLine("\n### Notes") | Out-Null; foreach ($n in $notes){ $sb.AppendLine($n.Node.InnerText) | Out-Null } }
        }
        $idx++
    }

    SafeWrite $mdPath $sb.ToString()

    # 检测问题
    $text = $sb.ToString()
    $lines = $text -split "`n"
    $problems = @()
    foreach ($line in $lines){
        $trim = $line.Trim()
        if ($trim -match '^\s*(\d{1,2})[\.、\)]') { $problems += $trim; continue }
        if ($trim -match '题' -and $trim.Length -lt 200 -and $trim -notmatch '^##') { $problems += $trim }
    }
    $problems = $problems | Where-Object { $_ -ne '' } | Select-Object -Unique

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

    # 清理临时
    Remove-Item -Recurse -Force $tmp -ErrorAction SilentlyContinue
    Write-Host "已为 $($f.Name) 生成 summary 和 $($problems.Count) 个 problemNN.cpp (放在 $outDir)"
}

Write-Host "全部完成。"
