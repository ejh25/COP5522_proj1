# COP5522 Project 1

## Clone

You need an SSH key on your GitHub account. Then:

```bash
git clone git@github.com:hdnate08/COP5522_proj1.git
cd COP5522_proj1
```

## GitHub CLI login (WSL)

`gh` is how we talk to GitHub from the terminal (PRs, reviews, repo settings). Log in once per machine.

1. Install the CLI if it is missing: https://cli.github.com/
2. Run:

```bash
gh auth login
```

3. Choose:

   - **GitHub.com**
   - **SSH**
   - Upload your SSH public key if prompted (`~/.ssh/id_rsa.pub` is fine). If GitHub says the key is already in use, that is OK — it is already on your account.
   - **Login with a web browser**

4. WSL usually cannot open a browser (`xdg-open` / `wslview` not found). Copy the one-time code, then in **Windows** open:

   https://github.com/login/device

   Paste the code, approve GitHub CLI, then go back to the terminal and press Enter. Do not Ctrl+C while it waits.

5. Confirm:

```bash
gh auth status
```

You should see your GitHub username and SSH as the git protocol.

### Where the login is stored

`gh` writes the token to `~/.config/gh/hosts.yml`. That file stays on this machine across reboots. Do not commit it, and do not put a token in this repo.

Keep a **personal access token** (`repo` scope) in a password manager if you want a copy you can recover on a new machine. Restore with:

```bash
gh auth login --with-token
```