Assume that $\alpha$ is the angle of the current square, and $\Delta \alpha$ is the increment of $\alpha$ in each recursion. The sides of the following two squares are:
$$
S_l = S \cdot \cos(\Delta \alpha) \\
S_r = S \cdot \sin(\Delta \alpha)
$$
Where $S_l$ is the side of the relatively left square, and $S_r$ is the side of the relatively right square.

Let $\beta = \alpha + \Delta \alpha$. The vertices of the next two squares are:
$$
\begin{equation}
\begin{split}

V_{ll} =& V_l + S_l \cdot (-\sin\beta, -\cos\beta)
\\ 
V_{lr} =& V_l + S_l \cdot (\cos\beta -\sin\beta, -\sin\beta - \cos\beta)
\\
V_{rl} =& V_r + S_r \cdot (\cos\beta -\sin\beta, -\sin\beta - \cos\beta)
\\
V_{rr} =& V_r + S_r \cdot (\cos\beta, -\sin\beta)

\end{split}
\end{equation}
$$
Where $V_l$ and $V_r$ are two vertices of the current square, $V_{ll}$ and $V_{lr}$ are two vertices of the next left square, and $V_{rl}$ and $V_{rr}$ are two vertices of the next right square.