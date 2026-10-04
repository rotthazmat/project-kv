# Kanto-Verse setup with GitHub Codespaces

Build a pokeemerald-expansion ROM entirely in the cloud. Nothing is installed on your PC except a small emulator to play the result.

**What you need:**

- A GitHub account
- A web browser
- [mGBA](https://mgba.io/downloads.html) to play the ROM (the Windows portable `.7z` is around 20 MB)

## 1. Fork the expansion into your own repository

1. Sign in to GitHub and open [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion).
2. Click **Fork** (top right).
3. On the fork page:
   - **Repository name:** `project-kv`
   - Leave **Copy the `master` branch only** checked. `master` is the stable branch the docs recommend.
4. Click **Create fork**.

You now have `github.com/<your-user>/project-kv`. This is your project.

## 2. Create a codespace

1. On your fork's page, click the green **Code** button.
2. Open the **Codespaces** tab.
3. Click **Create codespace on master**.

A VS Code editor opens in your browser, running on a Linux machine in the cloud. The first startup takes a minute or two.

## 3. Install the build tools (once per codespace)

Open the terminal (**Ctrl+`** or menu **Terminal → New Terminal**) and run:

```bash
sudo apt update
sudo apt install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3
```

These are the official Ubuntu dependencies from the expansion's `docs/install/linux/UBUNTU.md`. They stay installed when you stop and restart the codespace. You only need to run this again if you delete the codespace and create a new one (see [step 8](#8-optional-install-the-tools-automatically) to automate it).

## 4. Build the ROM

In the same terminal:

```bash
make -j$(nproc)
```

The first build takes several minutes because it also compiles the helper tools. Later builds only recompile what changed and are much faster.

When it finishes, `pokeemerald.gba` appears in the file explorer on the left.

## 5. Play it

1. In the left file explorer, right-click `pokeemerald.gba` and choose **Download**.
2. Open the downloaded file in mGBA.

If the game boots to the intro, your setup works. Do this before changing anything, so you know any later errors come from your edits and not the setup.

## 6. Make a first change

Try a small edit to learn the edit → build → play loop. This example edits directly in the codespace. For day-to-day work, edit on your PC instead (see [Local editing workflow](#local-editing-workflow)).

1. Open `src/starter_choose.c` and find the `sStarterMon` list.
2. Replace one starter, for example `SPECIES_TREECKO` with `SPECIES_BULBASAUR`.
3. Run `make -j$(nproc)` again.
4. Download the new `pokeemerald.gba` and start a new game in mGBA.

## 7. Save your work

The ROM itself is ignored by Git (it's always rebuilt from source). Save your source changes by committing and pushing them to your fork:

```bash
git add -A
git commit -m "Change starter to Bulbasaur"
git push
```

You can also use the **Source Control** panel (the branch icon on the left) instead of typing these commands.

Commit after every change that builds and works. If something breaks later, you can always go back.

## 8. Optional: install the tools automatically

To skip step 3 whenever you create a fresh codespace, add a dev container config to your repository.

1. Create the file `.devcontainer/devcontainer.json` with:

   ```json
   {
     "name": "project-kv",
     "image": "mcr.microsoft.com/devcontainers/base:ubuntu",
     "postCreateCommand": "sudo apt update && sudo apt install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3"
   }
   ```

2. Commit and push it (step 7).

New codespaces created after this install the tools by themselves. An existing codespace only picks it up after **Rebuild Container** (F1 → *Codespaces: Rebuild Container*).

## Free usage limits

Personal GitHub accounts get a monthly free allowance for Codespaces: compute hours (counted per CPU core, so a 2-core machine uses them twice as fast) and a storage quota. Check the current numbers under **GitHub → Settings → Billing and plans**.

To stay within the allowance:

- **Stop the codespace when you're done.** Go to [github.com/codespaces](https://github.com/codespaces), open **⋯** next to it, and choose **Stop codespace**. It also stops on its own after 30 minutes idle.
- **Keep the default 2-core machine.** It's enough for this project.
- **Keep one codespace.** Delete any extras from the same page.
- **Push your work regularly.** Inactive codespaces are deleted automatically after a while, and anything not pushed is lost.

## Local editing workflow

Code and maps are edited on your PC. The codespace is only used to build the ROM. GitHub sits in the middle, and changes move only when you push and pull:

```text
Your PC (code + Porymap)  ──push──▶  GitHub  ──pull──▶  Codespace (make → .gba)
```

### One-time local setup (already done)

The local folder `C:\Users\Jose\Projects\apps\kanto-verse` is connected to the fork. For reference, it was set up with:

```bash
git init -b master
git config core.autocrlf false
git remote add origin git@github.com:rotthazmat/project-kv.git
git fetch --depth 1 origin master
git checkout master
```

- `core.autocrlf false` keeps Linux line endings, which the build in the codespace expects.
- `--depth 1` downloads only the latest version of the code, without the full history, to save disk space.
- The remote uses SSH (`git@github.com:...`), so pushing and pulling authenticate with your SSH key in `C:\Users\Jose\.ssh`. No GitHub sign-in is needed.

### Every session

1. **On your PC:** run `git pull` to get any changes made elsewhere.
2. **Edit:** change code (with Claude Code) or maps (with Porymap).
3. **On your PC:** commit and push:

   ```bash
   git add -A
   git commit -m "Describe the change"
   git push
   ```

4. **In the codespace:** pull, build and download the ROM:

   ```bash
   git pull
   make -j$(nproc)
   ```

   Then right-click `pokeemerald.gba` → **Download** and play it in mGBA.

5. **Stop the codespace** when you're done.

If the build fails, fix the error on your PC and repeat steps 3–4. Avoid editing files in the codespace. If you do, push them from there and `git pull` on your PC before continuing, or the two copies will conflict.

### Map editing with Porymap

1. Download the Windows release of [Porymap](https://github.com/huderlem/porymap/releases).
2. Open it and choose **File → Open Project**, then select `C:\Users\Jose\Projects\apps\kanto-verse`.
3. Edit maps, save, then commit and push as above.

Porymap works directly on the source files, so it doesn't need a local build.

## Coming back later

1. Go to [github.com/codespaces](https://github.com/codespaces).
2. Click your existing `project-kv` codespace to resume it. Don't create a new one each time.
3. Follow [Every session](#every-session).

## Learning the expansion

Read the `docs/` folder in your repository and the expansion's [README](https://github.com/rh-hideout/pokeemerald-expansion#readme). The README links to the community Discord.
